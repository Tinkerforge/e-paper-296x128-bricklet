/* e-paper-296x128-v2-bricklet
 * Copyright (C) 2018-2021 Olaf Lüke <olaf@tinkerforge.com>
 *
 * ssd1675a.h: SSD1675A driver
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

#ifndef SSD1675A_H
#define SSD1675A_H

#include <stdint.h>
#include <stdbool.h>

#define SSD1675A_PIXEL_W 128
#define SSD1675A_PIXEL_H 296

#define SSD1675A_SPI_BUFFER_SIZE 256
#define SSD1675A_DISPLAY_BUFFER_SIZE (SSD1675A_PIXEL_W * SSD1675A_PIXEL_H / 8)


#define SSD1675A_CALIBRATION_PAGE 1
#define SSD1675A_CALIBRATION_MAGIC1 0x12345678
#define SSD1675A_CALIBRATION_MAGIC2 0x23456789
#define SSD1675A_CALIBRATION_MAGIC1_POS 0
#define SSD1675A_CALIBRATION_DISPLAY_TYPE_POS 1
#define SSD1675A_CALIBRATION_MAGIC2_POS 2
#define SSD1675A_CALIBRATION_DISPLAY_DRIVER_POS 3

typedef struct {
	uint8_t spi_data[SSD1675A_SPI_BUFFER_SIZE];
	uint16_t spi_data_length;

    bool initialize;
	bool reset;
	bool draw;

    uint8_t display_bw[SSD1675A_DISPLAY_BUFFER_SIZE];
    uint8_t display_red[SSD1675A_DISPLAY_BUFFER_SIZE];

	uint16_t read_chunk_offset_bw;
	uint16_t read_chunk_offset_red;

	uint8_t draw_status;
	uint8_t update_mode;

	uint8_t display_type;
	bool display_type_new;

	uint8_t display_driver;
	bool display_driver_new;
} SSD1675A;

extern SSD1675A ssd1675a;

void ssd1675a_init(void);
void ssd1675a_tick(void);
void ssd1675a_trigger_draw(void);


#define SSD1675A_COLOR_BW  0
#define SSD1675A_COLOR_RED 1

#define SSD1675A_DRIVER_OUTPUT                               0x01
#define SSD1675A_SOURCE_DRIVING_VOLTAGE                      0x04
#define SSD1675A_DEEP_SLEEP                                  0x10
#define SSD1675A_DATA_ENTRY_SEQUENCE                         0x11
#define SSD1675A_SW_RESET                                    0x12
#define SSD1675A_DISPLAY_UPDATE_SEQUENCE_RUN                 0x20
#define SSD1675A_DISPLAY_UPDATE_SEQUENCE_CFG                 0x22
#define SSD1675A_DATA_START_TRANSMISSION_1                   0x24
#define SSD1675A_DATA_START_TRANSMISSION_2                   0x26
#define SSD1675A_WRITE_VCOM_REGISTER                         0x2C
#define SSD1675A_WRITE_LUT_REGISTER                          0x32
#define SSD1675A_DUMMY_LINE_PERIOD                           0x3A
#define SSD1675A_GATE_LINE_WIDTH                             0x3B
#define SSD1675A_BORDER_WAVEFORM                             0x3C
#define SSD1675A_RAM_X_START_END                             0x44
#define SSD1675A_RAM_Y_START_END                             0x45
#define SSD1675A_RAM_X_COUNTER                               0x4E
#define SSD1675A_RAM_Y_COUNTER                               0x4F
#define SSD1675A_ANALOG_BLOCK                                0x74
#define SSD1675A_DIGITAL_BLOCK                               0x7E

#define SSD1680_DRIVER_CONTROL                               0x01
#define SSD1680_GATE_VOLTAGE                                 0x03
#define SSD1680_SOURCE_VOLTAGE                               0x04
#define SSD1680_INIT_SETTING                                 0x08
#define SSD1680_INIT_WRITE_REG                               0x09
#define SSD1680_INIT_READ_REG                                0x0A
#define SSD1680_BOOSTER_SOFT_START                           0x0C
#define SSD1680_DEEP_SLEEP                                   0x10
#define SSD1680_DATA_MODE                                    0x11
#define SSD1680_SW_RESET                                     0x12
#define SSD1680_HV_DETECT                                    0x14
#define SSD1680_VCI_DETECT                                   0x15
#define SSD1680_TEMP_CONTROL                                 0x18
#define SSD1680_TEMP_WRITE                                   0x1A
#define SSD1680_TEMP_READ                                    0x1B
#define SSD1680_EXTTEMP_WRITE                                0x1C
#define SSD1680_MASTER_ACTIVATE                              0x20
#define SSD1680_DISP_CTRL1                                   0x21
#define SSD1680_DISP_CTRL2                                   0x22
#define SSD1680_WRITE_BWRAM                                  0x24
#define SSD1680_WRITE_REDRAM                                 0x26
#define SSD1680_READ_RAM                                     0x27
#define SSD1680_VCOM_SENSE                                   0x28
#define SSD1680_VCOM_DURATION                                0x29
#define SSD1680_WRITE_VCOM_OTP                               0x2A
#define SSD1680_WRITE_VCOM_CTRL                              0x2B
#define SSD1680_WRITE_VCOM_REG                               0x2C
#define SSD1680_READ_OTP                                     0x2D
#define SSD1680_READ_USERID                                  0x2E
#define SSD1680_READ_STATUS                                  0x2F
#define SSD1680_WRITE_WS_OTP                                 0x30
#define SSD1680_LOAD_WS_OTP                                  0x31
#define SSD1680_WRITE_LUT                                    0x32
#define SSD1680_CRC_CALC                                     0x34
#define SSD1680_CRC_READ                                     0x35
#define SSD1680_PROG_OTP                                     0x36
#define SSD1680_WRITE_DISPLAY_OPT                            0x37
#define SSD1680_WRITE_USERID                                 0x38
#define SSD1680_OTP_PROGMODE                                 0x39
#define SSD1680_WRITE_BORDER                                 0x3C
#define SSD1680_END_OPTION                                   0x3F
#define SSD1680_SET_RAMXPOS                                  0x44
#define SSD1680_SET_RAMYPOS                                  0x45
#define SSD1680_AUTOWRITE_RED                                0x46
#define SSD1680_AUTOWRITE_BW                                 0x47
#define SSD1680_SET_RAMXCOUNT                                0x4E
#define SSD1680_SET_RAMYCOUNT                                0x4F
#define SSD1680_NOP                                          0xFF

#endif
