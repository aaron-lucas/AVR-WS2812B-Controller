/* ============================================================================
 * LED Strip Controller - ATtiny85 MCU-based control of WS2812B LED Strips.
 *
 * patterns.
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

#include "patterns.h"
#include "definitions.h"
#include "rainbow_table.h"

// Fast pseudo-random number generator
// Sourced from https://www.avrfreaks.net/forum/tiny-fast-prng
static uint8_t rand(void);

// Color order for cycle-all pattern
static enum color cycle_all[NUM_CYCLE_COLORS] = {
    COLOR_RED,
    COLOR_GREEN,
    COLOR_PURPLE,
    COLOR_ORANGE,
    COLOR_BLUE,
    COLOR_WHITE,
    COLOR_PINK,
    COLOR_YELLOW,
    COLOR_CYAN
};

// State variables used for pattern timing and colors
// 'tick count' counts the update ticks to allow updates to trigger at a
// specific number of update ticks (allows timing control)
// 'state' holds the current pattern state (defined arbitrarily for each pattern)
static uint16_t tick_count  = 0;
static uint8_t  state       = 0;

void update_pattern(struct rgb_data *leds, enum pattern pat, bool reset) {
    if (reset) {
        tick_count = 0;
        state = 0;
    }

    switch (pat) {
        case PATTERN_SOLID_RED:     show_solid_color(leds, COLOR_RED);                  break;
        case PATTERN_SOLID_GREEN:   show_solid_color(leds, COLOR_GREEN);                break;
        case PATTERN_SOLID_PURPLE:  show_solid_color(leds, COLOR_PURPLE);               break;
        case PATTERN_SOLID_ORANGE:  show_solid_color(leds, COLOR_ORANGE);               break;
        case PATTERN_SOLID_BLUE:    show_solid_color(leds, COLOR_BLUE);                 break;
        case PATTERN_SOLID_WHITE:   show_solid_color(leds, COLOR_WHITE);                break;
        case PATTERN_SOLID_PINK:    show_solid_color(leds, COLOR_PINK);                 break;
        case PATTERN_SOLID_YELLOW:  show_solid_color(leds, COLOR_YELLOW);               break;
        case PATTERN_SOLID_CYAN:    show_solid_color(leds, COLOR_CYAN);                 break;
        case PATTERN_CYCLE:         cycle_colors(leds, cycle_all, NUM_COLORS, reset);   break;
        case PATTERN_DISCO:         random_colors(leds);                                break;
        case PATTERN_RAINBOW_FADE:  rainbow_fade(leds, reset);                          break;
        default:                                                                        break;
    };
}

void show_solid_color(struct rgb_data *leds, enum color c) {
    show_solid_rgb(leds, RGB_OF(c));
}

void show_solid_rgb(struct rgb_data *leds, struct rgb_data rgb) {
    for (uint8_t led = 0; led < NUM_LEDS; led++)
        leds[led] = rgb;
}

void cycle_colors(struct rgb_data *leds, enum color *order, uint8_t num_colors, bool reset) {
    if (reset) {
        show_solid_color(leds, order[0]);
    } 

    if (tick_count++ == UPDATE_TICKS_CSC) {
        tick_count = 0;
        state = (state + 1) % NUM_CYCLE_COLORS;
        show_solid_color(leds, order[state]);
    }
}

void random_colors(struct rgb_data *leds) {
    if (tick_count++ == UPDATE_TICKS_RC) {
        tick_count = 0;
        for (uint8_t led = 0; led < NUM_LEDS; led++) {
            enum color selection = rand() % 8;//NUM_COLORS;
            leds[led] = colors[selection];
        }
    }
}

void rainbow_fade(struct rgb_data *leds, bool reset) {
    static uint8_t speed_counter = 0;
    static struct rgb_data current_color = HEX_TO_RGB(0xFF0000);

    if (reset) {
        speed_counter = 0;
        current_color = HEX_TO_RGB(0xFF0000);
    }

    if (tick_count++ == UPDATE_TICKS_RF) {
        tick_count = 0;
        if (state == 0) {
            // Red to green (slow)
            if (speed_counter++ == 3) {
                speed_counter = 0;
                current_color.red--;
                if (++current_color.green == 0x04)
                    state = 1;
            }
        } else if (state == 1) {
            // Red to green (fast)
            current_color.red--;
            if (++current_color.green == 0xFF)
                state = 2;
        } else if (state == 2) {
            // Green to blue
            current_color.green--;
            if (++current_color.blue == 0xFF)
                state = 3;
        } else if (state == 3) {
            // Blue to red
            current_color.blue--;
            if (++current_color.red == 0xFF) {
                state = 0;
                speed_counter = 0;
            }
        }
    }

    show_solid_rgb(leds, current_color);
}

static uint8_t rand(void) {
    static uint8_t seed = 0xAA, a = 0;
    seed ^= seed << 3;
    seed ^= seed >> 5;
    seed ^= a++ >> 2;

    return seed;
}

