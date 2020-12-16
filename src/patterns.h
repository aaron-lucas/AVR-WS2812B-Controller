/* ============================================================================
 * LED Strip Controller - ATtiny85 MCU-based control of WS2812B LED Strips.
 *
 * patterns.h
 *
 * Functions to display pretty patterns on the LED strip
 * Created On: 2020/12/08
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

#ifndef PATTERNS_H
#define PATTERNS_H

#include "rgb_data.h"

#include <stdbool.h>

enum pattern {
    FIRST_PATTERN = 0,
    PATTERN_SOLID_RED = 0,
    PATTERN_SOLID_GREEN,
    PATTERN_SOLID_PURPLE,
    PATTERN_SOLID_ORANGE,
    PATTERN_SOLID_BLUE,
    PATTERN_SOLID_WHITE,
    PATTERN_SOLID_PINK,
    PATTERN_SOLID_YELLOW,
    PATTERN_SOLID_CYAN,
    PATTERN_CYCLE,
    PATTERN_DISCO,
    PATTERN_RAINBOW_FADE,
    NUM_PATTERNS
};

void update_pattern(struct rgb_data *leds, enum pattern pat, bool reset);

void show_solid_color(struct rgb_data *leds, enum color c);

void show_solid_rgb(struct rgb_data *leds, struct rgb_data rgb);

#define UPDATE_TICKS_CSC    7 * UPDATE_FREQ
#define NUM_CYCLE_COLORS    9
void cycle_colors(struct rgb_data *leds, enum color *order, uint8_t num_colors, bool reset);

#define UPDATE_TICKS_RC     4
#define INITIAL_SEED_RC     0x69
void random_colors(struct rgb_data *leds);

#define UPDATE_TICKS_RF     2
void rainbow_fade(struct rgb_data *leds, bool reset);

#endif
