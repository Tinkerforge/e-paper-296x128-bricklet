/* e-paper-296x128-v2-bricklet
 * Copyright (C) 2018 Olaf Lüke <olaf@tinkerforge.com>
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

typedef struct {
	uint8_t spi_data[SSD1675A_SPI_BUFFER_SIZE];
	uint16_t spi_data_length;

    bool initialize;
	bool reset;

	uint16_t draw_bw_x_start;
	uint8_t draw_bw_y_start;
	uint16_t draw_bw_x_end;
	uint8_t draw_bw_y_end;
	bool draw_bw;

	uint16_t draw_red_x_start;
	uint8_t draw_red_y_start;
	uint16_t draw_red_x_end;
	uint8_t draw_red_y_end;
	bool draw_red;

    uint8_t display_bw[SSD1675A_DISPLAY_BUFFER_SIZE];
    uint8_t display_red[SSD1675A_DISPLAY_BUFFER_SIZE];

	uint16_t read_chunk_offset_bw;
	uint16_t read_chunk_offset_red;

	uint8_t draw_status;
	uint8_t update_mode;
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

#endif