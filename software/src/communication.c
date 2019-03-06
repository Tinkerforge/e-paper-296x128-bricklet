/* e-paper-296x128-bricklet
 * Copyright (C) 2019 Olaf Lüke <olaf@tinkerforge.com>
 *
 * communication.c: TFP protocol message handling
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

#include "communication.h"

#include "bricklib2/utility/communication_callback.h"
#include "bricklib2/protocols/tfp/tfp.h"
#include "bricklib2/utility/util_definitions.h"

#include "ssd1675a.h"
#include "gui.h"

BootloaderHandleMessageResponse handle_message(const void *message, void *response) {
	switch(tfp_get_fid_from_message(message)) {
		case FID_DRAW: return draw(message);
		case FID_GET_DRAW_STATUS: return get_draw_status(message, response);
		case FID_WRITE_BLACK_WHITE_LOW_LEVEL: return write_black_white_low_level(message);
		case FID_READ_BLACK_WHITE_LOW_LEVEL: return read_black_white_low_level(message, response);
		case FID_WRITE_RED_LOW_LEVEL: return write_red_low_level(message);
		case FID_READ_RED_LOW_LEVEL: return read_red_low_level(message, response);
		case FID_FILL_DISPLAY: return fill_display(message);
		case FID_DRAW_TEXT: return draw_text(message);
		case FID_DRAW_LINE: return draw_line(message);
		case FID_DRAW_BOX: return draw_box(message);
		case FID_SET_UPDATE_MODE: return set_update_mode(message);
		case FID_GET_UPDATE_MODE: return get_update_mode(message, response);
		default: return HANDLE_MESSAGE_RESPONSE_NOT_SUPPORTED;
	}
}


BootloaderHandleMessageResponse draw(const Draw *data) {
	ssd1675a.draw        = true;
	ssd1675a.draw_status = E_PAPER_296X128_DRAW_STATUS_COPYING;

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_draw_status(const GetDrawStatus *data, GetDrawStatus_Response *response) {
	response->header.length = sizeof(GetDrawStatus_Response);
	response->draw_status   = ssd1675a.draw_status;

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

BootloaderHandleMessageResponse write_color_low_level(const WriteBlackWhiteLowLevel *data, uint8_t *buffer) {
	if((data->x_start > data->x_end) || (data->y_start > data->y_end)) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	if((data->x_end >= SSD1675A_PIXEL_H) || (data->y_end >= SSD1675A_PIXEL_W)) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	const uint16_t length = MIN(data->pixels_length - data->pixels_chunk_offset, 54*8);
	const uint16_t x_num = data->x_end - data->x_start + 1;

	uint16_t x = data->x_start + (data->pixels_chunk_offset % x_num);
	uint16_t y = data->y_start + (data->pixels_chunk_offset / x_num);

	uint16_t counter = 0;
	for(; y <= data->y_end; y++) {
		for(; x <= data->x_end; x++) {
			const uint16_t data_index = counter / 8;
			const uint8_t  data_bit   = counter % 8;
			gui_set_pixel(x, y, data->pixels_chunk_data[data_index] & (1 << data_bit), buffer);

			counter++;
			if(counter == length) {
				break;
			}
		}

		if(counter == length) {
			break;
		}
		x = data->x_start;
	}

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse read_color_low_level(const ReadBlackWhiteLowLevel *data, ReadBlackWhiteLowLevel_Response *response, uint8_t *buffer, uint16_t *read_chunk_offset) {
	if((data->x_start > data->x_end) || (data->y_start > data->y_end)) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	if((data->x_end >= SSD1675A_PIXEL_H) || (data->y_end >= SSD1675A_PIXEL_W)) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	memset(response->pixels_chunk_data, 0, 58);

	response->header.length = sizeof(ReadBlackWhiteLowLevel_Response);
	response->pixels_length = (data->x_end - data->x_start + 1)*(data->y_end - data->y_start + 1);
	response->pixels_chunk_offset = *read_chunk_offset;

	const uint16_t length = MIN(response->pixels_length - response->pixels_chunk_offset, 58*8);
	const uint16_t x_num = data->x_end - data->x_start + 1;

	uint16_t x = data->x_start + (response->pixels_chunk_offset % x_num);
	uint16_t y = data->y_start + (response->pixels_chunk_offset / x_num);

	uint16_t counter = 0;
	for(; y <= data->y_end; y++) {
		for(; x <= data->x_end; x++) {
			const uint16_t data_index = counter / 8;
			const uint8_t  data_bit   = counter % 8;
			response->pixels_chunk_data[data_index] |= (gui_get_pixel(x, y, buffer) << data_bit);

			counter++;
			if(counter == length) {
				break;
			}
		}

		if(counter == length) {
			break;
		}
		x = data->x_start;
	}

	*read_chunk_offset += counter;
	if(*read_chunk_offset == response->pixels_length) {
		*read_chunk_offset = 0;
	}

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

BootloaderHandleMessageResponse write_black_white_low_level(const WriteBlackWhiteLowLevel *data) {
	if(ssd1675a.update_mode == E_PAPER_296X128_UPDATE_MODE_DELTA) {
		return write_color_low_level(data, ssd1675a.display_red);
	}

	return write_color_low_level(data, ssd1675a.display_bw);
}

BootloaderHandleMessageResponse read_black_white_low_level(const ReadBlackWhiteLowLevel *data, ReadBlackWhiteLowLevel_Response *response) {
	if(ssd1675a.update_mode == E_PAPER_296X128_UPDATE_MODE_DELTA) {
		return read_color_low_level(data, response, ssd1675a.display_red, &ssd1675a.read_chunk_offset_bw);
	}
	return read_color_low_level(data, response, ssd1675a.display_bw, &ssd1675a.read_chunk_offset_bw);
}

BootloaderHandleMessageResponse write_red_low_level(const WriteRedLowLevel *data) {
	if(ssd1675a.update_mode == E_PAPER_296X128_UPDATE_MODE_DELTA) {
		return HANDLE_MESSAGE_RESPONSE_EMPTY;
	}

	return write_color_low_level((const WriteBlackWhiteLowLevel *)data, ssd1675a.display_red);
}

BootloaderHandleMessageResponse read_red_low_level(const ReadRedLowLevel *data, ReadRedLowLevel_Response *response) {
	if(ssd1675a.update_mode == E_PAPER_296X128_UPDATE_MODE_DELTA) {
		memset(response->pixels_chunk_data, 0, 58);

		response->header.length = sizeof(ReadRedLowLevel_Response);
		response->pixels_length = 0;
		response->pixels_chunk_offset = 0;
		return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
	}
	return read_color_low_level((const ReadBlackWhiteLowLevel *)data, (ReadBlackWhiteLowLevel_Response *)response, ssd1675a.display_red, &ssd1675a.read_chunk_offset_red);
}

BootloaderHandleMessageResponse fill_display(const FillDisplay *data) {
	if(data->color > E_PAPER_296X128_COLOR_RED) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	memset(ssd1675a.display_bw,  data->color == E_PAPER_296X128_COLOR_WHITE ? 0xFF : 0x00, SSD1675A_DISPLAY_BUFFER_SIZE);
	memset(ssd1675a.display_red, data->color == E_PAPER_296X128_COLOR_RED   ? 0xFF : 0x00, SSD1675A_DISPLAY_BUFFER_SIZE);

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse draw_text(const DrawText *data) {
	if((data->position_x >= SSD1675A_PIXEL_H) ||
	   (data->position_y >= SSD1675A_PIXEL_W)) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	if(data->font > E_PAPER_296X128_FONT_24X32) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	if(data->orientation > E_PAPER_296X128_ORIENTATION_VERTICAL) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	if(data->color > E_PAPER_296X128_COLOR_RED) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	gui_draw_text(data->position_x, data->position_y, strnlen(data->text, 50), data->text, data->font, data->color, data->orientation);

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse draw_line(const DrawLine *data) {
	if((data->position_x_start >= SSD1675A_PIXEL_H) ||
	   (data->position_x_end >= SSD1675A_PIXEL_H) ||
	   (data->position_y_start >= SSD1675A_PIXEL_W) ||
	   (data->position_y_end >= SSD1675A_PIXEL_W)) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	if(data->color > E_PAPER_296X128_COLOR_RED) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	gui_draw_line(data->position_x_start, data->position_y_start, data->position_x_end, data->position_y_end, data->color);

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse draw_box(const DrawBox *data) {
	if((data->position_x_start >= SSD1675A_PIXEL_H) ||
	   (data->position_x_end >= SSD1675A_PIXEL_H) ||
	   (data->position_y_start >= SSD1675A_PIXEL_W) ||
	   (data->position_y_end >= SSD1675A_PIXEL_W)) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}	

	if(data->color > E_PAPER_296X128_COLOR_RED) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	gui_draw_box(data->position_x_start, data->position_y_start, data->position_x_end, data->position_y_end, data->fill, data->color);

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse set_update_mode(const SetUpdateMode *data) {
	if(data->update_mode > E_PAPER_296X128_UPDATE_MODE_DELTA) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	if(ssd1675a.update_mode != E_PAPER_296X128_UPDATE_MODE_DELTA) {
		if(data->update_mode == E_PAPER_296X128_UPDATE_MODE_DELTA) {
			// In delta mode we save the currnet bw image and the new bw image.
			// To get this started we set both to the same buffer.
			// This assumes that the user did not use any red color before.
			memcpy(ssd1675a.display_red, ssd1675a.display_bw, SSD1675A_DISPLAY_BUFFER_SIZE);
		}
	}

	if(ssd1675a.update_mode == E_PAPER_296X128_UPDATE_MODE_DELTA) {
		if(data->update_mode != E_PAPER_296X128_UPDATE_MODE_DELTA) {
			// If we turn delta mode off again, zero red buffer
			memset(ssd1675a.display_red, 0, SSD1675A_DISPLAY_BUFFER_SIZE);
		}
	}

	ssd1675a.update_mode = data->update_mode;
	ssd1675a.initialize  = true;

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_update_mode(const GetUpdateMode *data, GetUpdateMode_Response *response) {
	response->header.length = sizeof(GetUpdateMode_Response);
	response->update_mode   = ssd1675a.update_mode;

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}


bool handle_draw_status_callback(void) {
	static bool is_buffered = false;
	static DrawStatus_Callback cb;
	static uint8_t last_draw_status = E_PAPER_296X128_DRAW_STATUS_IDLE;

	if(!is_buffered) {
		if(last_draw_status != ssd1675a.draw_status) {
			tfp_make_default_header(&cb.header, bootloader_get_uid(), sizeof(DrawStatus_Callback), FID_CALLBACK_DRAW_STATUS);
			last_draw_status = ssd1675a.draw_status;
			cb.draw_status = last_draw_status;
		} else {
			return false;
		}
	}

	if(bootloader_spitfp_is_send_possible(&bootloader_status.st)) {
		bootloader_spitfp_send_ack_and_message(&bootloader_status, (uint8_t*)&cb, sizeof(DrawStatus_Callback));
		is_buffered = false;
		return true;
	} else {
		is_buffered = true;
	}

	return false;
}

void communication_tick(void) {
	communication_callback_tick();
}

void communication_init(void) {
	communication_callback_init();
}
