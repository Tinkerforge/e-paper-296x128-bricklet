/* e-paper-296x128-v2-bricklet
 * Copyright (C) 2019 Olaf Lüke <olaf@tinkerforge.com>
 *
 * gui.c: Simple GUI drawing functions for E-Paper
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

#include "gui.h"

#include "ssd1675a.h"
#include "communication.h"

#include "bricklib2/utility/util_definitions.h"

#include "font.inc"

inline void gui_set_pixel(const uint16_t column, const uint16_t row, const bool value, uint8_t *buffer) {
	if((column >= SSD1675A_PIXEL_H) || (row >= SSD1675A_PIXEL_W)) {
		return;
	}

	const uint8_t  display_bit   = 7 - (row % 8);
	const uint16_t display_index = (295-column) * SSD1675A_PIXEL_W / 8 + row / 8;
	if(value) {
		buffer[display_index] |= (1 << display_bit);
	} else {
		buffer[display_index] &= ~(1 << display_bit);
	}
}

inline void gui_set_pixel_color(const uint16_t column, const uint16_t row, const uint8_t color) {
	if((column >= SSD1675A_PIXEL_H) || (row >= SSD1675A_PIXEL_W)) {
		return;
	}

	const uint8_t  display_bit   = 7 - (row % 8);
	const uint16_t display_index = (295-column) * SSD1675A_PIXEL_W / 8 + row / 8;

	if(ssd1675a.update_mode == E_PAPER_296X128_UPDATE_MODE_DELTA) {
		if(color == E_PAPER_296X128_COLOR_BLACK) {
			ssd1675a.display_red[display_index]  &= ~(1 << display_bit);
		} else {
			ssd1675a.display_red[display_index]  |=  (1 << display_bit);
		}
	} else {
		if(color == E_PAPER_296X128_COLOR_BLACK) {
			ssd1675a.display_bw[display_index]  &= ~(1 << display_bit);
			ssd1675a.display_red[display_index] &= ~(1 << display_bit);
		} else if(color == E_PAPER_296X128_COLOR_WHITE) {
			ssd1675a.display_bw[display_index]  |=  (1 << display_bit);
			ssd1675a.display_red[display_index] &= ~(1 << display_bit);
		} else {
			ssd1675a.display_bw[display_index]  &= ~(1 << display_bit);
			ssd1675a.display_red[display_index] |=  (1 << display_bit);
		}
	}
}

inline bool gui_get_pixel(const uint16_t column, const uint16_t row, uint8_t *buffer) {
	const uint8_t  display_bit   = 7 - (row % 8);
	const uint16_t display_index = (295-column) * SSD1675A_PIXEL_W / 8 + row / 8;

	return buffer[display_index] & (1 << display_bit);
}

void gui_draw_text_horizontal(const uint16_t column, const uint16_t row, const uint8_t text_length, const char *text, const uint8_t col_mul, const uint8_t row_mul, const uint8_t color) {
	for(uint8_t i = 0; i < text_length; i++) {
		for(uint8_t j = 0; j < 6; j++) {
			const uint8_t data = ((j == 5) ? 0 : font[(uint8_t)text[i]*5 + j]);
			for(uint8_t k = 0; k < 8; k++) {
				if(data & (1 << k)) {
					const uint16_t pixel_column = j*col_mul + column + i*6*col_mul;
					const uint16_t pixel_row    = k*row_mul+row;
					if((row_mul == 1) && (col_mul == 1)) {
						gui_set_pixel_color(pixel_column, pixel_row, color);
					} else {
						const int16_t x_end = pixel_column+col_mul-1;
						const int16_t y_end = pixel_row-row_mul+1;
						if((x_end < 0) || (y_end < 0)) {
							continue;
						}
						gui_draw_box(pixel_column, pixel_row, x_end, y_end, true, color);
					}
				}
			}
		}
	}
}

void gui_draw_text_vertical(const uint16_t column, const uint16_t row, const uint8_t text_length, const char *text, const uint8_t col_mul, const uint8_t row_mul, const uint8_t color) {
	for(uint8_t i = 0; i < text_length; i++) {
		for(uint8_t j = 0; j < 6; j++) {
			const uint8_t data = ((j == 5) ? 0 : font[(uint8_t)text[i]*5 + j]);
			for(uint8_t k = 0; k < 8; k++) {
				if(data & (1 << k)) {
					const uint16_t pixel_column = k*row_mul + column;
					const int16_t  pixel_row    = row - j*col_mul - i*6*col_mul;
					if(pixel_row < 0) {
						continue;
					}
					if((row_mul == 1) && (col_mul == 1)) {
						gui_set_pixel_color(pixel_column, pixel_row, color);
					} else {
						const int16_t x_end = pixel_column+col_mul-1;
						const int16_t y_end = pixel_row-row_mul+1;
						if((x_end < 0) || (y_end < 0)) {
							continue;
						}
						gui_draw_box(pixel_column, pixel_row, x_end, y_end, true, color);
					}
				}
			}
		}
	}
}

void gui_draw_text(const uint16_t column, const uint16_t row, const uint8_t text_length, const char *text, const uint8_t font_type, const uint8_t color, const uint8_t orientation) {
	uint8_t col_mul = 1;
	uint8_t row_mul = 1;
	switch(font_type) {
		case E_PAPER_296X128_FONT_6X8:   col_mul = 1; row_mul = 1; break;
		case E_PAPER_296X128_FONT_6X16:  col_mul = 1; row_mul = 2; break;
		case E_PAPER_296X128_FONT_6X24:  col_mul = 1; row_mul = 3; break;
		case E_PAPER_296X128_FONT_6X32:  col_mul = 1; row_mul = 4; break;
		case E_PAPER_296X128_FONT_12X16: col_mul = 2; row_mul = 2; break;
		case E_PAPER_296X128_FONT_12X24: col_mul = 2; row_mul = 3; break;
		case E_PAPER_296X128_FONT_12X32: col_mul = 2; row_mul = 4; break;
		case E_PAPER_296X128_FONT_18X24: col_mul = 3; row_mul = 3; break;
		case E_PAPER_296X128_FONT_18X32: col_mul = 3; row_mul = 4; break;
		case E_PAPER_296X128_FONT_24X32: col_mul = 4; row_mul = 4; break;
	}

	if(orientation == E_PAPER_296X128_ORIENTATION_HORIZONTAL) {
		gui_draw_text_horizontal(column, row, text_length, text, col_mul, row_mul, color);
	} else {
		gui_draw_text_vertical(column, row, text_length, text, col_mul, row_mul, color);
	}


}

void gui_draw_box(const uint16_t x_start, const uint16_t y_start, const uint16_t x_end, const uint16_t y_end, const bool fill, const uint8_t color) {
	const uint16_t x0 = MIN(x_start, x_end);
	const uint16_t y0 = MIN(y_start, y_end);
	const uint16_t x1 = MAX(x_start, x_end);
	const uint16_t y1 = MAX(y_start, y_end);

	for(uint16_t x = x0; x <= x1; x++) {
		for(uint16_t y = y0; y <= y1; y++) {
			if(fill) {
				gui_set_pixel_color(x, y, color);
			} else {
				if((x == x0) || (y == y0) ||
				   (x == x1) || (y == y1)) {
					gui_set_pixel_color(x, y, color);
				} else {
					gui_set_pixel_color(x, y, !color);
				}
			}
		}
	}
}

void gui_draw_line_low(const uint16_t x0, const uint16_t y0, const uint16_t x1, const uint16_t y1, const uint8_t color) {
	int16_t dx = x1 - x0;
	int16_t dy = y1 - y0;
	int16_t yi = 1;
	if(dy < 0) {
		yi = -1;
		dy = -dy;
	}

	int16_t D = 2*dy - dx;
	int16_t y = y0;

	for(uint16_t x = x0; x <= x1; x++) {
		gui_set_pixel_color(x, y, color);
		if(D > 0) {
			y = y + yi;
			D = D - 2*dx;
		}
		D = D + 2*dy;
	}
}

void gui_draw_line_high(const uint16_t x0, const uint16_t y0, const uint16_t x1, const uint16_t y1, const uint8_t color) {
	int16_t dx = x1 - x0;
	int16_t dy = y1 - y0;
	int16_t xi = 1;
	if(dx < 0) {
		xi = -1;
		dx = -dx;
	}

	int16_t D = 2*dx - dy;
	int16_t x = x0;

	for(uint16_t y = y0; y <= y1; y++) {
		gui_set_pixel_color(x, y, color);
		if(D > 0) {
			x = x + xi;
			D = D - 2*dy;
		}
		D = D + 2*dx;
	}
}

// See https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
void gui_draw_line(const uint16_t x0, const uint16_t y0, const uint16_t x1, const uint16_t y1, const uint8_t color) {
	if(ABS(((int32_t)y1) - y0) < ABS(((int32_t)x1) - x0)) {
		if(x0 > x1) {
			gui_draw_line_low(x1, y1, x0, y0, color);
		} else {
			gui_draw_line_low(x0, y0, x1, y1, color);
		}
	} else {
		if(y0 > y1) {
			gui_draw_line_high(x1, y1, x0, y0, color);
		} else {
			gui_draw_line_high(x0, y0, x1, y1, color);
		}
	}
}
