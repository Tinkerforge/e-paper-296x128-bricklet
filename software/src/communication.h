/* e-paper-296x128-bricklet
 * Copyright (C) 2019 Olaf Lüke <olaf@tinkerforge.com>
 *
 * communication.h: TFP protocol message handling
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

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>
#include <stdbool.h>

#include "bricklib2/protocols/tfp/tfp.h"
#include "bricklib2/bootloader/bootloader.h"

// Default functions
BootloaderHandleMessageResponse handle_message(const void *data, void *response);
void communication_tick(void);
void communication_init(void);

// Constants
#define E_PAPER_296X128_DRAW_STATUS_IDLE 0
#define E_PAPER_296X128_DRAW_STATUS_COPYING 1
#define E_PAPER_296X128_DRAW_STATUS_DRAWING 2

#define E_PAPER_296X128_COLOR_BLACK 0
#define E_PAPER_296X128_COLOR_WHITE 1
#define E_PAPER_296X128_COLOR_RED 2

#define E_PAPER_296X128_FONT_6X8 0
#define E_PAPER_296X128_FONT_6X16 1
#define E_PAPER_296X128_FONT_6X24 2
#define E_PAPER_296X128_FONT_6X32 3
#define E_PAPER_296X128_FONT_12X16 4
#define E_PAPER_296X128_FONT_12X24 5
#define E_PAPER_296X128_FONT_12X32 6
#define E_PAPER_296X128_FONT_18X24 7
#define E_PAPER_296X128_FONT_18X32 8
#define E_PAPER_296X128_FONT_24X32 9

#define E_PAPER_296X128_ORIENTATION_HORIZONTAL 0
#define E_PAPER_296X128_ORIENTATION_VERTICAL 1

#define E_PAPER_296X128_UPDATE_MODE_DEFAULT 0
#define E_PAPER_296X128_UPDATE_MODE_BLACK_WHITE 1
#define E_PAPER_296X128_UPDATE_MODE_DELTA 2

#define E_PAPER_296X128_DISPLAY_BLACK_WHITE_RED 0
#define E_PAPER_296X128_DISPLAY_BLACK_WHITE_GRAY 1

#define E_PAPER_296X128_BOOTLOADER_MODE_BOOTLOADER 0
#define E_PAPER_296X128_BOOTLOADER_MODE_FIRMWARE 1
#define E_PAPER_296X128_BOOTLOADER_MODE_BOOTLOADER_WAIT_FOR_REBOOT 2
#define E_PAPER_296X128_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_REBOOT 3
#define E_PAPER_296X128_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_ERASE_AND_REBOOT 4

#define E_PAPER_296X128_BOOTLOADER_STATUS_OK 0
#define E_PAPER_296X128_BOOTLOADER_STATUS_INVALID_MODE 1
#define E_PAPER_296X128_BOOTLOADER_STATUS_NO_CHANGE 2
#define E_PAPER_296X128_BOOTLOADER_STATUS_ENTRY_FUNCTION_NOT_PRESENT 3
#define E_PAPER_296X128_BOOTLOADER_STATUS_DEVICE_IDENTIFIER_INCORRECT 4
#define E_PAPER_296X128_BOOTLOADER_STATUS_CRC_MISMATCH 5

#define E_PAPER_296X128_STATUS_LED_CONFIG_OFF 0
#define E_PAPER_296X128_STATUS_LED_CONFIG_ON 1
#define E_PAPER_296X128_STATUS_LED_CONFIG_SHOW_HEARTBEAT 2
#define E_PAPER_296X128_STATUS_LED_CONFIG_SHOW_STATUS 3

// Function and callback IDs and structs
#define FID_DRAW 1
#define FID_GET_DRAW_STATUS 2
#define FID_WRITE_BLACK_WHITE_LOW_LEVEL 3
#define FID_READ_BLACK_WHITE_LOW_LEVEL 4
#define FID_WRITE_RED_LOW_LEVEL 5
#define FID_READ_RED_LOW_LEVEL 6
#define FID_FILL_DISPLAY 7
#define FID_DRAW_TEXT 8
#define FID_DRAW_LINE 9
#define FID_DRAW_BOX 10
#define FID_SET_UPDATE_MODE 12
#define FID_GET_UPDATE_MODE 13
#define FID_SET_DISPLAY 14
#define FID_GET_DISPLAY 15

#define FID_CALLBACK_DRAW_STATUS 11

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) Draw;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetDrawStatus;

typedef struct {
	TFPMessageHeader header;
	uint8_t draw_status;
} __attribute__((__packed__)) GetDrawStatus_Response;

typedef struct {
	TFPMessageHeader header;
	uint16_t x_start;
	uint8_t y_start;
	uint16_t x_end;
	uint8_t y_end;
	uint16_t pixels_length;
	uint16_t pixels_chunk_offset;
	uint8_t pixels_chunk_data[54];
} __attribute__((__packed__)) WriteBlackWhiteLowLevel;

typedef struct {
	TFPMessageHeader header;
	uint16_t x_start;
	uint8_t y_start;
	uint16_t x_end;
	uint8_t y_end;
} __attribute__((__packed__)) ReadBlackWhiteLowLevel;

typedef struct {
	TFPMessageHeader header;
	uint16_t pixels_length;
	uint16_t pixels_chunk_offset;
	uint8_t pixels_chunk_data[58];
} __attribute__((__packed__)) ReadBlackWhiteLowLevel_Response;

typedef struct {
	TFPMessageHeader header;
	uint16_t x_start;
	uint8_t y_start;
	uint16_t x_end;
	uint8_t y_end;
	uint16_t pixels_length;
	uint16_t pixels_chunk_offset;
	uint8_t pixels_chunk_data[54];
} __attribute__((__packed__)) WriteRedLowLevel;

typedef struct {
	TFPMessageHeader header;
	uint16_t x_start;
	uint8_t y_start;
	uint16_t x_end;
	uint8_t y_end;
} __attribute__((__packed__)) ReadRedLowLevel;

typedef struct {
	TFPMessageHeader header;
	uint16_t pixels_length;
	uint16_t pixels_chunk_offset;
	uint8_t pixels_chunk_data[58];
} __attribute__((__packed__)) ReadRedLowLevel_Response;

typedef struct {
	TFPMessageHeader header;
	uint8_t color;
} __attribute__((__packed__)) FillDisplay;

typedef struct {
	TFPMessageHeader header;
	uint16_t position_x;
	uint8_t position_y;
	uint8_t font;
	uint8_t color;
	uint8_t orientation;
	char text[50];
} __attribute__((__packed__)) DrawText;

typedef struct {
	TFPMessageHeader header;
	uint16_t position_x_start;
	uint8_t position_y_start;
	uint16_t position_x_end;
	uint8_t position_y_end;
	uint8_t color;
} __attribute__((__packed__)) DrawLine;

typedef struct {
	TFPMessageHeader header;
	uint16_t position_x_start;
	uint8_t position_y_start;
	uint16_t position_x_end;
	uint8_t position_y_end;
	bool fill;
	uint8_t color;
} __attribute__((__packed__)) DrawBox;

typedef struct {
	TFPMessageHeader header;
	uint8_t draw_status;
} __attribute__((__packed__)) DrawStatus_Callback;

typedef struct {
	TFPMessageHeader header;
	uint8_t update_mode;
} __attribute__((__packed__)) SetUpdateMode;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetUpdateMode;

typedef struct {
	TFPMessageHeader header;
	uint8_t update_mode;
} __attribute__((__packed__)) GetUpdateMode_Response;

typedef struct {
	TFPMessageHeader header;
	uint8_t display;
} __attribute__((__packed__)) SetDisplay;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetDisplay;

typedef struct {
	TFPMessageHeader header;
	uint8_t display;
} __attribute__((__packed__)) GetDisplay_Response;


// Function prototypes
BootloaderHandleMessageResponse draw(const Draw *data);
BootloaderHandleMessageResponse get_draw_status(const GetDrawStatus *data, GetDrawStatus_Response *response);
BootloaderHandleMessageResponse write_black_white_low_level(const WriteBlackWhiteLowLevel *data);
BootloaderHandleMessageResponse read_black_white_low_level(const ReadBlackWhiteLowLevel *data, ReadBlackWhiteLowLevel_Response *response);
BootloaderHandleMessageResponse write_red_low_level(const WriteRedLowLevel *data);
BootloaderHandleMessageResponse read_red_low_level(const ReadRedLowLevel *data, ReadRedLowLevel_Response *response);
BootloaderHandleMessageResponse fill_display(const FillDisplay *data);
BootloaderHandleMessageResponse draw_text(const DrawText *data);
BootloaderHandleMessageResponse draw_line(const DrawLine *data);
BootloaderHandleMessageResponse draw_box(const DrawBox *data);
BootloaderHandleMessageResponse set_update_mode(const SetUpdateMode *data);
BootloaderHandleMessageResponse get_update_mode(const GetUpdateMode *data, GetUpdateMode_Response *response);
BootloaderHandleMessageResponse set_display(const SetDisplay *data);
BootloaderHandleMessageResponse get_display(const GetDisplay *data, GetDisplay_Response *response);

// Callbacks
bool handle_draw_status_callback(void);

#define COMMUNICATION_CALLBACK_TICK_WAIT_MS 1
#define COMMUNICATION_CALLBACK_HANDLER_NUM 1
#define COMMUNICATION_CALLBACK_LIST_INIT \
	handle_draw_status_callback, \


#endif
