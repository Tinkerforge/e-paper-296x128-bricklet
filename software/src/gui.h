/* e-paper-296x128-v2-bricklet
 * Copyright (C) 2019 Olaf Lüke <olaf@tinkerforge.com>
 *
 * gui.h: Simple GUI drawing functions for E-Paper
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

#ifndef GUI_H
#define GUI_H

#include <stdint.h>
#include <stdbool.h>

void gui_set_pixel(const uint16_t column, const uint16_t row, const bool value, uint8_t *buffer);
void gui_set_pixel_color(const uint16_t column, const uint16_t row, const uint8_t color);
bool gui_get_pixel(const uint16_t column, const uint16_t row, uint8_t *buffer);
void gui_draw_text(const uint16_t column, const uint16_t row, const uint8_t text_length, const char *text, const uint8_t font_type, const uint8_t color, const uint8_t orientation);
void gui_draw_box(const uint16_t x_start, const uint16_t y_start, const uint16_t x_end, const uint16_t y_end, const bool fill, const uint8_t color);
void gui_draw_line_low(const uint16_t x0, const uint16_t y0, const uint16_t x1, const uint16_t y1, const uint8_t color);
void gui_draw_line_high(const uint16_t x0, const uint16_t y0, const uint16_t x1, const uint16_t y1, const uint8_t color);
void gui_draw_line(const uint16_t x0, const uint16_t y0, const uint16_t x1, const uint16_t y1, const uint8_t color);

#endif