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

#include "rgb_data.h"

static inline uint8_t difference(uint8_t a, uint8_t b) {
    if (a > b)
        return a - b;
    else 
        return b - a;
}

static inline void swap(uint8_t *a, uint8_t *b) {
    uint8_t temp = *a;
    *a = *b;
    *b = temp;
}

const struct rgb_data colors[NUM_COLORS] = {
    HEX_TO_RGB(0xC00000),       // RED
    HEX_TO_RGB(0xFF2000),       // ORANGE
    HEX_TO_RGB(0xEA5200),       // YELLOW
    HEX_TO_RGB(0x206000),       // GREEN
    HEX_TO_RGB(0x001080),       // BLUE
    HEX_TO_RGB(0x6E00FF),       // PURPLE
    HEX_TO_RGB(0xFF009A),       // PINK
    HEX_TO_RGB(0x00777A),       // CYAN
    HEX_TO_RGB(0x867565)        // WHITE
};

/* struct hsv_data rgb_to_hsv(struct rgb_data rgb) { */
/*     uint8_t *c_max = &rgb.red; */
/*     uint8_t *c_mid = &rgb.green; */
/*     uint8_t *c_min = &rgb.blue; */

/*     if (*c_mid < *c_min) */
/*         swap(c_mid, c_min); */
/*     if (*c_max < *c_min) */
/*         swap(c_max, c_min); */
/*     if (*c_max < *c_mid) */
/*         swap(c_max, c_mid); */

/*     uint8_t delta = *c_max - *c_min; */

/*     struct hsv_data hsv; */
/*     if (delta == 0) { */
/*         hsv.hue = 0; */
/*     } else if (*c_max == rgb.red) { */
/*         hsv.hue = (uint16_t)(rgb.green - rgb.blue); */
/*     } */
    
/* } */

/* struct rgb_data combine_colors(struct rgb_data c1, struct rgb_data c2, uint8_t weight) { */
/*     struct rgb_data delta = { */
/*         .green = difference(c1.green, c2.green), */
/*         .red = difference(c1.red, c2.red), */
/*         .blue = difference(c1.blue, c2.blue) */
/*     }; */

    
/* } */
