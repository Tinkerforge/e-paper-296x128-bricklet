/* e-paper-296x128-v2-bricklet
 * Copyright (C) 2018 Olaf Lüke <olaf@tinkerforge.com>
 *
 * ssd1675a.c: SSD1675A driver
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "ssd1675a.h"

#include "communication.h"

#include "configs/config_ssd1675a.h"
#include "bricklib2/os/coop_task.h"
#include "bricklib2/utility/util_definitions.h"

#include "xmc_spi.h"
#include "xmc_gpio.h"
#include "xmc_scu.h"

// Waveforms

// 00 = VSS  =   0V
// 01 = VSH1 =  15V
// 10 = VSL  = -15V
// 11 = VSH2 =   5V

// https://forums.pimoroni.com/t/my-inky-phat-clock-refresh-speed-question/6955/5

#define SSD1675_LUT_BLACK_WHITE                                                                             \
/*    Phase 0     Phase 1     Phase 2     Phase 3     Phase 4     Phase 5     Phase 6                    */ \
/*    A B C D     A B C D     A B C D     A B C D     A B C D     A B C D     A B C D                    */ \
	0b00100010, 0b00010001, 0b00010000, 0b00000000, 0b00010000, 0b00000000, 0b00000000, /* lut0 (black)  */ \
	0b00010001, 0b10001000, 0b10000000, 0b10000000, 0b10000000, 0b00000000, 0b00000000, /* lut1 (white)  */ \
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, /* lut2 (red)    */ \
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, /* lut3 (red)    */ \
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, /* lut4 (vcom)   */ \
                                                                                                            \
/*  Duration       | Repeats           */                                                                   \
/*   A   B   C   D |                   */                                                                   \
	 4, 24,  4, 22,  1,     /* Phase 0 */                                                                   \
	10, 10, 10, 10,  2,     /* Phase 1 */                                                                   \
     0,  0,  0,  0,  0,     /* Phase 2 */                                                                   \
     0,  0,  0,  0,  0,     /* Phase 3 */                                                                   \
     0,  0,  0,  0,  0,     /* Phase 4 */                                                                   \
     0,  0,  0,  0,  0,     /* Phase 5 */                                                                   \
     0,  0,  0,  0,  0,     /* Phase 6 */


#define SSD1675_LUT_DELTA                                                                                   \
/*    Phase 0     Phase 1     Phase 2     Phase 3     Phase 4     Phase 5     Phase 6                    */ \
/*    A B C D     A B C D     A B C D     A B C D     A B C D     A B C D     A B C D                    */ \
	0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, /* lut0 (none)   */ \
	0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, /* lut1 (b->w)   */ \
    0b01000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, /* lut2 (w->b)   */ \
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, /* lut3 (none)   */ \
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, /* lut4 (vcom)   */ \
                                                                                                            \
/*  Duration       | Repeats           */                                                                   \
/*   A   B   C   D |                   */                                                                   \
	24,  0,  0,  0,  1,     /* Phase 0 */                                                                   \
	 0,  0,  0,  0,  0,     /* Phase 1 */                                                                   \
     0,  0,  0,  0,  0,     /* Phase 2 */                                                                   \
     0,  0,  0,  0,  0,     /* Phase 3 */                                                                   \
     0,  0,  0,  0,  0,     /* Phase 4 */                                                                   \
     0,  0,  0,  0,  0,     /* Phase 5 */                                                                   \
     0,  0,  0,  0,  0,     /* Phase 6 */

#define SSD1675_LUT                                                                                         \
/*    Phase 0     Phase 1     Phase 2     Phase 3     Phase 4     Phase 5     Phase 6                    */ \
/*    A B C D     A B C D     A B C D     A B C D     A B C D     A B C D     A B C D                    */ \
	0b00100010, 0b00010001, 0b00010000, 0b00000000, 0b00010000, 0b00000000, 0b00000000, /* lut0 (black)  */ \
	0b00010001, 0b10001000, 0b10000000, 0b10000000, 0b10000000, 0b00000000, 0b00000000, /* lut1 (white)  */ \
	0b01101010, 0b10011011, 0b10011011, 0b10011011, 0b10011011, 0b00000000, 0b00000000, /* lut2 (red)    */ \
	0b01101010, 0b10011011, 0b10011011, 0b10011011, 0b10011011, 0b00000000, 0b00000000, /* lut3 (red)    */ \
	0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, /* lut4 (vcom)   */ \
                                                                                                            \
/*  Duration       | Repeats           */                                                                   \
/*   A   B   C   D |	               */                                                                   \
	 4, 24,  4, 22,  1,     /* Phase 0 */                                                                   \
	10, 10, 10, 10,  2,     /* Phase 1 */                                                                   \
	 0,  0,  0,  0,  0,     /* Phase 2 */                                                                   \
	 0,  0,  0,  0,  0,     /* Phase 3 */                                                                   \
	 4,  4,  8, 60,  7,     /* Phase 4 */                                                                   \
	 0,  0,  0,  0,  0,     /* Phase 5 */                                                                   \
	 0,  0,  0,  0,  0      /* Phase 6 */


#define SSD1675_LUT_SIZE 70
#define ssd1675a_tx_irq_handler IRQ_Hdlr_12

CoopTask ssd1675a_task;
SSD1675A ssd1675a;

const uint8_t ssd1675a_init_conf[] = {
	1, SSD1675A_SW_RESET,
	0xFF, // wait until idle
	2, SSD1675A_ANALOG_BLOCK,                    0x54,
	2, SSD1675A_DIGITAL_BLOCK,                   0x3B,
	4, SSD1675A_DRIVER_OUTPUT,                   0x27, 0x01, 0x00,
	2, SSD1675A_DUMMY_LINE_PERIOD,               0x35,
	2, SSD1675A_GATE_LINE_WIDTH,                 0x04,
	2, SSD1675A_DATA_ENTRY_SEQUENCE,             0x03,
	4, SSD1675A_SOURCE_DRIVING_VOLTAGE,          0x41, 0xa8, 0x32, // 15V, 5V, -15V
	2, SSD1675A_WRITE_VCOM_REGISTER,             0x68,
	2, SSD1675A_BORDER_WAVEFORM,                 0x33,
//	71, SSD1675A_WRITE_LUT_REGISTER,             SSD1675_LUT
};

static const uint8_t ssd1675a_lut_default[SSD1675_LUT_SIZE]     = {SSD1675_LUT};
static const uint8_t ssd1675a_lut_delta[SSD1675_LUT_SIZE]       = {SSD1675_LUT_DELTA};
static const uint8_t ssd1675a_lut_black_white[SSD1675_LUT_SIZE] = {SSD1675_LUT_BLACK_WHITE};

// Set pointers to read/write buffer
// With this the compiler can properly optimize the access!
uint8_t *spi_data_read = ssd1675a.spi_data;
uint8_t *spi_data_write = ssd1675a.spi_data;
uint8_t *spi_data_write_end = ssd1675a.spi_data;

void __attribute__((optimize("-O3"))) __attribute__ ((section (".ram_code"))) ssd1675a_tx_irq_handler(void) {
	// Max fill level is 32.
	const uint8_t num = MIN(32-XMC_USIC_CH_TXFIFO_GetLevel(SSD1675A_USIC), spi_data_write_end - spi_data_write);
	switch(num) {
        case 32: SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 31: SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 30: SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 29: SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 28: SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 27: SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 26: SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 25: SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 24: SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 23: SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 22: SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 21: SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 20: SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 19: SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 18: SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 17: SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 16: SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 15: SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 14: SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 13: SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 12: SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 11: SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 10: SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 9:  SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 8:  SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 7:  SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 6:  SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 5:  SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 4:  SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 3:  SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 2:  SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
		case 1:  SSD1675A_USIC->IN[0] = *spi_data_write; spi_data_write++;
	}

	if(spi_data_write >= spi_data_write_end) {
		XMC_USIC_CH_TXFIFO_DisableEvent(SSD1675A_USIC, XMC_USIC_CH_TXFIFO_EVENT_CONF_STANDARD);
	}
}


void ssd1675a_write_calibration(uint8_t display) {
	uint32_t page[EEPROM_PAGE_SIZE/sizeof(uint32_t)];
	page[SSD1675A_CALIBRATION_MAGIC_POS]   = SSD1675A_CALIBRATION_MAGIC;
	page[SSD1675A_CALIBRATION_DISPLAY_POS] = display;

	if(!bootloader_write_eeprom_page(SSD1675A_CALIBRATION_PAGE, page)) {
		// TODO: Error handling?
	}
}


void ssd1675a_read_calibration(void) {
	uint32_t page[EEPROM_PAGE_SIZE/sizeof(uint32_t)];

	bootloader_read_eeprom_page(SSD1675A_CALIBRATION_PAGE, page);

	// The magic number is not where it is supposed to be.
	// This is either our first startup or something went wrong.
	// We initialize the calibration data with sane default values.
	if(page[SSD1675A_CALIBRATION_MAGIC_POS] != SSD1675A_CALIBRATION_MAGIC) {
		ssd1675a.display = 0;

		ssd1675a_write_calibration(0);
		return;
	}

	ssd1675a.display = page[SSD1675A_CALIBRATION_DISPLAY_POS];
}

void ssd1675a_spi_task_transceive(const uint8_t *data, const uint32_t length, XMC_SPI_CH_SLAVE_SELECT_t slave) {
	memcpy(ssd1675a.spi_data, data, length);
	ssd1675a.spi_data_length = length;
	spi_data_write = ssd1675a.spi_data;
	spi_data_write_end = ssd1675a.spi_data + length;

	// Fill FIFO with as much data as possible
	XMC_SPI_CH_ClearStatusFlag(SSD1675A_USIC, XMC_SPI_CH_STATUS_FLAG_MSLS);
	XMC_USIC_CH_TXFIFO_DisableEvent(SSD1675A_USIC, XMC_USIC_CH_TXFIFO_EVENT_CONF_STANDARD);
	while((!XMC_USIC_CH_TXFIFO_IsFull(SSD1675A_USIC)) && (spi_data_write < spi_data_write_end)) {
		SSD1675A_USIC->IN[0] = *spi_data_write;
		spi_data_write++;
	}
	NVIC_ClearPendingIRQ(SSD1675A_IRQ_TX);

	if(spi_data_write < spi_data_write_end) {
		// If we dont yet have everything written, enable fifo
		XMC_USIC_CH_TXFIFO_EnableEvent(SSD1675A_USIC, XMC_USIC_CH_TXFIFO_EVENT_CONF_STANDARD);
	}

	// Enable slave select, FIFO transfer will start here
	XMC_SPI_CH_EnableSlaveSelect(SSD1675A_USIC, slave);

	// Wait for data to be written through TX IRQ
	while((spi_data_write < spi_data_write_end) || !XMC_USIC_CH_TXFIFO_IsEmpty(SSD1675A_USIC)) {
		coop_task_yield();
	}

	// The FIFO will automatically disable slave select when all data is written
	// We wait until slave select is low here. Otherwise there may still be up to
	// 7 bits send and we have a race condition 
	// (C/D pin can changed before the bits are out).
	while(!XMC_GPIO_GetInput(SSD1675A_SELECT_PIN)) {
		// We test for this be reading the actualy slave select pin,
		// there does not seem to be any reliable status flag for this?
		coop_task_yield();
	}
}

void ssd1675a_task_write_data(const uint8_t *data, const uint32_t length) {
	XMC_GPIO_SetOutputHigh(SSD1675A_CD_PIN);
	if(length > SSD1675A_SPI_BUFFER_SIZE) {
		for(uint16_t i = 0; i < length/SSD1675A_SPI_BUFFER_SIZE + 1; i++) {
			uint16_t partial_length = MIN(SSD1675A_SPI_BUFFER_SIZE, length - i*SSD1675A_SPI_BUFFER_SIZE);
			if(partial_length != 0) {
				ssd1675a_spi_task_transceive(&data[i*SSD1675A_SPI_BUFFER_SIZE], partial_length, XMC_SPI_CH_SLAVE_SELECT_0);
			}
		}
	} else {
		ssd1675a_spi_task_transceive(data, length, XMC_SPI_CH_SLAVE_SELECT_0);
	}
}

void ssd1675a_task_write_command(const uint8_t command) {
	XMC_GPIO_SetOutputLow(SSD1675A_CD_PIN);
	ssd1675a_spi_task_transceive(&command, 1, XMC_SPI_CH_SLAVE_SELECT_0);
}

void ssd1675a_init_spi(void) {
	// USIC channel configuration
	const XMC_SPI_CH_CONFIG_t channel_config = {
		.baudrate       = SSD1675A_SPI_BAUDRATE,
		.bus_mode       = XMC_SPI_CH_BUS_MODE_MASTER,
		.selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
		.parity_mode    = XMC_USIC_CH_PARITY_MODE_NONE
	};

	// MOSI pin configuration
	const XMC_GPIO_CONFIG_t mosi_pin_config = {
		.mode             = SSD1675A_MOSI_PIN_AF,
		.output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH
	};

    // SELECT pin configuration
	const XMC_GPIO_CONFIG_t select_pin_config = {
		.mode             = SSD1675A_SELECT_PIN_AF,
		.output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH
	};

	// SCLK pin configuration
	const XMC_GPIO_CONFIG_t sclk_pin_config = {
		.mode             = SSD1675A_SCLK_PIN_AF,
		.output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH
	};

	// Initialize USIC channel in SPI master mode
	XMC_SPI_CH_Init(SSD1675A_USIC, &channel_config);
	SSD1675A_USIC->SCTR &= ~USIC_CH_SCTR_PDL_Msk; // Set passive data level to 0

	XMC_SPI_CH_SetSlaveSelectPolarity(SSD1675A_USIC, XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS);
	XMC_SPI_CH_SetBitOrderMsbFirst(SSD1675A_USIC);

	XMC_SPI_CH_SetWordLength(SSD1675A_USIC, 8);
	XMC_SPI_CH_SetFrameLength(SSD1675A_USIC, 64);

	XMC_SPI_CH_SetTransmitMode(SSD1675A_USIC, XMC_SPI_CH_MODE_STANDARD);

	// Configure the clock polarity and clock delay
	XMC_SPI_CH_ConfigureShiftClockOutput(SSD1675A_USIC,
									     XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_0_DELAY_ENABLED,
									     XMC_SPI_CH_BRG_SHIFT_CLOCK_OUTPUT_SCLK);

	// Configure Leading/Trailing delay
	XMC_SPI_CH_SetSlaveSelectDelay(SSD1675A_USIC, 2);

	// Disable FEM, such that FIFO will automatically disable slave select
	XMC_SPI_CH_DisableFEM(SSD1675A_USIC);

	// SPI Mode: CPOL=1 and CPHA=1
	SSD1675A_USIC_CHANNEL->DX1CR |= USIC_CH_DX1CR_DPOL_Msk;

	// Configure transmit FIFO
	XMC_USIC_CH_TXFIFO_Configure(SSD1675A_USIC, 32, XMC_USIC_CH_FIFO_SIZE_32WORDS, 8);

	// Set service request for tx FIFO transmit interrupt
	XMC_USIC_CH_TXFIFO_SetInterruptNodePointer(SSD1675A_USIC, XMC_USIC_CH_TXFIFO_INTERRUPT_NODE_POINTER_STANDARD, SSD1675A_SERVICE_REQUEST_TX);  // IRQ SSD1675a_IRQ_TX

	//Set priority and enable NVIC node for transmit interrupt
	NVIC_SetPriority(SSD1675A_IRQ_TX, SSD1675A_IRQ_TX_PRIORITY);
	XMC_SCU_SetInterruptControl(SSD1675A_IRQ_TX, SSD1675A_IRQ_TX_SCU);
	NVIC_EnableIRQ(SSD1675A_IRQ_TX);

	// Start SPI
	XMC_SPI_CH_Start(SSD1675A_USIC);

	// Configure slave select pin
	XMC_GPIO_Init(SSD1675A_SELECT_PIN, &select_pin_config);

	// Configure SCLK pin
	XMC_GPIO_Init(SSD1675A_SCLK_PIN, &sclk_pin_config);

	// Configure MOSI pin
	XMC_GPIO_Init(SSD1675A_MOSI_PIN, &mosi_pin_config);

	XMC_SPI_CH_EnableSlaveSelect(SSD1675A_USIC, XMC_SPI_CH_SLAVE_SELECT_0);
}

void ssd1675a_task_wait_until_idle(void) {
	while(XMC_GPIO_GetInput(SSD1675A_BUSY_PIN)) { 
		coop_task_sleep_ms(1);
	}
}

void ssd1675a_task_set_window(const uint16_t x_start, const uint16_t x_end, const uint16_t y_start, const uint16_t y_end) {
	const uint8_t x[] = {x_start & 0xFF, x_end & 0xFF};
	const uint8_t y[] = {y_start & 0xFF, y_start >> 8, y_end & 0xFF, y_end >> 8};

	ssd1675a_task_write_command(SSD1675A_RAM_X_START_END);
	ssd1675a_task_write_data(x, 2);
	ssd1675a_task_write_command(SSD1675A_RAM_Y_START_END);
	ssd1675a_task_write_data(y, 4);
}


void ssd1675a_task_set_counter(const uint16_t x_count, const uint16_t y_count) {
	const uint8_t x[] = {x_count & 0xFF};
	const uint8_t y[] = {y_count & 0xFF, y_count >> 8};

	ssd1675a_task_write_command(SSD1675A_RAM_X_COUNTER);
	ssd1675a_task_write_data(x, 1);
	ssd1675a_task_write_command(SSD1675A_RAM_Y_COUNTER);
	ssd1675a_task_write_data(y, 2);
}

void ssd1675a_task_write_display(const uint8_t color) {
	const uint16_t x = 0;
	const uint16_t y = 0;
	const uint16_t width = SSD1675A_PIXEL_W;
	const uint16_t height = SSD1675A_PIXEL_H;

	ssd1675a_task_set_window(x/8, ((x+width)/8) - 1, y, y+height - 1);
	coop_task_sleep_ms(2);
	ssd1675a_task_set_counter(x/8, y);
	coop_task_sleep_ms(2);

	if(color == SSD1675A_COLOR_BW) {
		ssd1675a_task_write_command(SSD1675A_DATA_START_TRANSMISSION_1);
		if(ssd1675a.update_mode == E_PAPER_296X128_UPDATE_MODE_DELTA) {
			for(uint16_t i = 0; i < SSD1675A_DISPLAY_BUFFER_SIZE/SSD1675A_SPI_BUFFER_SIZE + 1; i++) {
				uint8_t btow[SSD1675A_SPI_BUFFER_SIZE] = {0};
				uint16_t partial_length = MIN(SSD1675A_SPI_BUFFER_SIZE, SSD1675A_DISPLAY_BUFFER_SIZE - i*SSD1675A_SPI_BUFFER_SIZE);
				if(partial_length != 0) {
					for(uint16_t j = 0; j < partial_length; j++) {
						uint16_t display_index = i*SSD1675A_SPI_BUFFER_SIZE + j;
						for(uint8_t bit = 0; bit < 8; bit++) {
							btow[j] |= ((!(ssd1675a.display_bw[display_index] & (1 << bit))) && (ssd1675a.display_red[display_index] & (1 << bit))) << bit;
						}
					}
					ssd1675a_task_write_data(btow, partial_length);
				}
			}
		} else {
			ssd1675a_task_write_data(ssd1675a.display_bw, SSD1675A_PIXEL_W*SSD1675A_PIXEL_H/8);
		}
	} else {
		ssd1675a_task_write_command(SSD1675A_DATA_START_TRANSMISSION_2);
		if(ssd1675a.update_mode == E_PAPER_296X128_UPDATE_MODE_DELTA) {
			for(uint16_t i = 0; i < SSD1675A_DISPLAY_BUFFER_SIZE/SSD1675A_SPI_BUFFER_SIZE + 1; i++) {
				uint8_t wtob[SSD1675A_SPI_BUFFER_SIZE] = {0};
				uint16_t partial_length = MIN(SSD1675A_SPI_BUFFER_SIZE, SSD1675A_DISPLAY_BUFFER_SIZE - i*SSD1675A_SPI_BUFFER_SIZE);
				if(partial_length != 0) {
					for(uint16_t j = 0; j < partial_length; j++) {
						uint16_t display_index = i*SSD1675A_SPI_BUFFER_SIZE + j;
						for(uint8_t bit = 0; bit < 8; bit++) {
							wtob[j] |= ((ssd1675a.display_bw[display_index] & (1 << bit)) && (!(ssd1675a.display_red[display_index] & (1 << bit)))) << bit;
						}
					}
					ssd1675a_task_write_data(wtob, partial_length);
				}
			}
		} else {
			ssd1675a_task_write_data(ssd1675a.display_red, SSD1675A_PIXEL_W*SSD1675A_PIXEL_H/8);
		}
	}
}

void ssd1675a_task_tick(void) {
	coop_task_sleep_ms(5);
    while(true) {
		if(ssd1675a.display_new) {
			ssd1675a.display_new = false;

			ssd1675a_write_calibration(ssd1675a.display);
		}

		if(ssd1675a.reset) {
			ssd1675a.reset = false;

			XMC_GPIO_SetOutputHigh(SSD1675A_RST_PIN);
			coop_task_sleep_ms(200);
			XMC_GPIO_SetOutputLow(SSD1675A_RST_PIN);
			coop_task_sleep_ms(200);
			XMC_GPIO_SetOutputHigh(SSD1675A_RST_PIN);
			coop_task_sleep_ms(200);
		}

		if(ssd1675a.initialize) {
			ssd1675a.initialize = false;

            uint16_t i = 0;
            while(i < sizeof(ssd1675a_init_conf)) {
                const uint8_t length = ssd1675a_init_conf[i];
				if(length == 0xFF) {
					ssd1675a_task_wait_until_idle();
					i++;
				} else {
					ssd1675a_task_write_command(ssd1675a_init_conf[i + 1]);
					if(length - 1 > 0) {
						ssd1675a_task_write_data(ssd1675a_init_conf + i + 2, length-1);
					}
					i += length + 1;
					coop_task_sleep_ms(1);
				}

				ssd1675a_task_write_command(SSD1675A_WRITE_LUT_REGISTER);
				switch(ssd1675a.update_mode) {
					case E_PAPER_296X128_UPDATE_MODE_BLACK_WHITE: ssd1675a_task_write_data(ssd1675a_lut_black_white, SSD1675_LUT_SIZE); break;
					case E_PAPER_296X128_UPDATE_MODE_DELTA:       ssd1675a_task_write_data(ssd1675a_lut_delta, SSD1675_LUT_SIZE);       break;
					case E_PAPER_296X128_UPDATE_MODE_DEFAULT: /* fall-through */
					default:                                      ssd1675a_task_write_data(ssd1675a_lut_default, SSD1675_LUT_SIZE);     break;
				}
				coop_task_sleep_ms(1);
            }
		}

		bool draw_done = false;

		if(ssd1675a.draw) {
			ssd1675a.draw_status = E_PAPER_296X128_DRAW_STATUS_COPYING;

			ssd1675a.draw = false;
			ssd1675a_task_write_display(SSD1675A_COLOR_BW);
			if((ssd1675a.update_mode != E_PAPER_296X128_UPDATE_MODE_BLACK_WHITE)) {
				ssd1675a_task_write_display(SSD1675A_COLOR_RED);
			}

			if(ssd1675a.update_mode == E_PAPER_296X128_UPDATE_MODE_DELTA) {
				memcpy(ssd1675a.display_bw, ssd1675a.display_red, SSD1675A_DISPLAY_BUFFER_SIZE);
			}

			draw_done = true;
		}

		if(draw_done) {
			ssd1675a.draw_status = E_PAPER_296X128_DRAW_STATUS_DRAWING;

			ssd1675a_task_write_command(SSD1675A_DISPLAY_UPDATE_SEQUENCE_CFG);
			uint8_t param = 0xC7;
			ssd1675a_task_write_data(&param, 1);
			ssd1675a_task_write_command(SSD1675A_DISPLAY_UPDATE_SEQUENCE_RUN);
			ssd1675a_task_wait_until_idle();

			ssd1675a.draw_status = E_PAPER_296X128_DRAW_STATUS_IDLE;
		}

        coop_task_yield();
    }
}

void ssd1675a_init(void) {
	// pin configuration input
	const XMC_GPIO_CONFIG_t input_pin_config = {
		.mode             = XMC_GPIO_MODE_INPUT_PULL_DOWN,
		.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
	};

	// pin configuration high
	const XMC_GPIO_CONFIG_t high_pin_config = {
		.mode             = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
		.output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH
	};

	XMC_GPIO_Init(SSD1675A_RST_PIN, &high_pin_config);
	XMC_GPIO_Init(SSD1675A_CD_PIN, &high_pin_config);
	XMC_GPIO_Init(SSD1675A_BUSY_PIN, &input_pin_config);

    memset(&ssd1675a, 0, sizeof(SSD1675A));
    ssd1675a.reset      = true;
    ssd1675a.initialize = true;
    ssd1675a.draw       = false;

    memset(ssd1675a.display_bw,  0x00, SSD1675A_PIXEL_W * SSD1675A_PIXEL_H / 8);
    memset(ssd1675a.display_red, 0x00, SSD1675A_PIXEL_W * SSD1675A_PIXEL_H / 8);

	ssd1675a_read_calibration();

    ssd1675a_init_spi();
    coop_task_init(&ssd1675a_task, ssd1675a_task_tick);
}

void ssd1675a_tick(void) {
    coop_task_tick(&ssd1675a_task);
}