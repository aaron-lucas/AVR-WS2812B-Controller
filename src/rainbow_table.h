/* ============================================================================
 * LED Strip Controller - ATtiny85 MCU-based control of WS2812B LED Strips.
 *
 * rainbow_table.h
 *
 * Lookup table of colors which make a rainbow
 * Created On: 2020/12/09
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

#ifndef RAINBOW_TABLE_H
#define RAINBOW_TABLE_H

#include <avr/pgmspace.h>

#define NUM_RAINBOW_COLORS  64

const struct rgb_data rainbow_table[NUM_RAINBOW_COLORS] PROGMEM = {
    { .red = 255, .green =   0, .blue =   0 },
    { .red = 255, .green =  23, .blue =   0 },
    { .red = 255, .green =  47, .blue =   0 },
    { .red = 255, .green =  71, .blue =   0 },
    { .red = 255, .green =  95, .blue =   0 },
    { .red = 255, .green = 119, .blue =   0 },
    { .red = 255, .green = 143, .blue =   0 },
    { .red = 255, .green = 167, .blue =   0 },
    { .red = 255, .green = 191, .blue =   0 },
    { .red = 255, .green = 215, .blue =   0 },
    { .red = 255, .green = 239, .blue =   0 },
    { .red = 247, .green = 255, .blue =   0 },
    { .red = 223, .green = 255, .blue =   0 },
    { .red = 199, .green = 255, .blue =   0 },
    { .red = 175, .green = 255, .blue =   0 },
    { .red = 151, .green = 255, .blue =   0 },
    { .red = 127, .green = 255, .blue =   0 },
    { .red = 103, .green = 255, .blue =   0 },
    { .red =  79, .green = 255, .blue =   0 },
    { .red =  55, .green = 255, .blue =   0 },
    { .red =  31, .green = 255, .blue =   0 },
    { .red =   7, .green = 255, .blue =   0 },
    { .red =   0, .green = 255, .blue =  15 },
    { .red =   0, .green = 255, .blue =  39 },
    { .red =   0, .green = 255, .blue =  63 },
    { .red =   0, .green = 255, .blue =  87 },
    { .red =   0, .green = 255, .blue = 111 },
    { .red =   0, .green = 255, .blue = 135 },
    { .red =   0, .green = 255, .blue = 159 },
    { .red =   0, .green = 255, .blue = 183 },
    { .red =   0, .green = 255, .blue = 207 },
    { .red =   0, .green = 255, .blue = 231 },
    { .red =   0, .green = 255, .blue = 255 },
    { .red =   0, .green = 231, .blue = 255 },
    { .red =   0, .green = 207, .blue = 255 },
    { .red =   0, .green = 183, .blue = 255 },
    { .red =   0, .green = 159, .blue = 255 },
    { .red =   0, .green = 135, .blue = 255 },
    { .red =   0, .green = 111, .blue = 255 },
    { .red =   0, .green =  87, .blue = 255 },
    { .red =   0, .green =  63, .blue = 255 },
    { .red =   0, .green =  39, .blue = 255 },
    { .red =   0, .green =  15, .blue = 255 },
    { .red =   7, .green =   0, .blue = 255 },
    { .red =  31, .green =   0, .blue = 255 },
    { .red =  55, .green =   0, .blue = 255 },
    { .red =  79, .green =   0, .blue = 255 },
    { .red = 103, .green =   0, .blue = 255 },
    { .red = 127, .green =   0, .blue = 255 },
    { .red = 151, .green =   0, .blue = 255 },
    { .red = 175, .green =   0, .blue = 255 },
    { .red = 199, .green =   0, .blue = 255 },
    { .red = 223, .green =   0, .blue = 255 },
    { .red = 247, .green =   0, .blue = 255 },
    { .red = 255, .green =   0, .blue = 239 },
    { .red = 255, .green =   0, .blue = 215 },
    { .red = 255, .green =   0, .blue = 191 },
    { .red = 255, .green =   0, .blue = 167 },
    { .red = 255, .green =   0, .blue = 143 },
    { .red = 255, .green =   0, .blue = 119 },
    { .red = 255, .green =   0, .blue =  95 },
    { .red = 255, .green =   0, .blue =  71 },
    { .red = 255, .green =   0, .blue =  47 },
    { .red = 255, .green =   0, .blue =  23 }
};

#endif
