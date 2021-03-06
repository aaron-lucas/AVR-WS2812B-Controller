/* ============================================================================
 * LED Strip Controller - ATtiny85 MCU-based control of WS2812B LED Strips.
 *
 * rgb_data.h
 *
 * Created On: 2020/12/02
 *
 * Copyright (C) 2020  Aaron Lucas
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 * aaronlucas98@gmail.com
 * https://github.com/aaron-lucas
 * ============================================================================
 */

#ifndef RGB_DATA_H
#define RGB_DATA_H

#include <stdint.h>
#include <avr/pgmspace.h>

#define NUM_COLORS  9

#define     HEX_TO_RGB(x)   (struct rgb_data) { .green = (uint8_t)((x & 0x0000FF00) >> 8),   \
                                                .red   = (uint8_t)((x & 0x00FF0000) >> 16),  \
                                                .blue  = (uint8_t) (x & 0x000000FF) }

struct rgb_data {
    uint8_t green;
    uint8_t red;
    uint8_t blue;
};

enum color {
    COLOR_RED,
    COLOR_ORANGE,
    COLOR_YELLOW,
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_PURPLE,
    COLOR_PINK,
    COLOR_CYAN, 
    COLOR_WHITE
};

struct rgb_data get_rgb(enum color c);

#endif
