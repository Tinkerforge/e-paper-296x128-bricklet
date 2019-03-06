/* e-paper-296x128-bricklet
 * Copyright (C) 2018 Olaf Lüke <olaf@tinkerforge.com>
 *
 * config_ssd1675a.h: Configuration for SSD1675A lcd controller
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

#ifndef CONFIG_SSD1675A_H
#define CONFIG_SSD1675A_H

#include "xmc_gpio.h"

#define SSD1675A_SPI_BAUDRATE         400000 // 1500000
#define SSD1675A_USIC_CHANNEL         USIC1_CH0
#define SSD1675A_USIC                 XMC_SPI1_CH0

#define SSD1675A_SCLK_PIN             P0_2
#define SSD1675A_SCLK_PIN_AF          (XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT8 | P0_2_AF_U1C0_SCLKOUT)

#define SSD1675A_SELECT_PIN           P4_7
#define SSD1675A_SELECT_PIN_AF        (XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7 | P4_7_AF_U1C0_SELO0)

#define SSD1675A_MOSI_PIN             P0_3
#define SSD1675A_MOSI_PIN_AF          (XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT9 | P0_3_AF_U1C0_DOUT0)

#define SSD1675A_SERVICE_REQUEST_TX   3

#define SSD1675A_IRQ_TX               12
#define SSD1675A_IRQ_TX_PRIORITY      1
#define SSD1675A_IRQ_TX_SCU           XMC_SCU_IRQCTRL_USIC1_SR3_IRQ12


#define SSD1675A_RST_PIN              P0_5
#define SSD1675A_CD_PIN               P0_4
#define SSD1675A_BUSY_PIN             P0_6

#endif