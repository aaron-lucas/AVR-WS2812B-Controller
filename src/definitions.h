/* ============================================================================
 * LED Strip Controller - ATtiny85 MCU-based control of WS2812B LED Strips.
 *
 * definitions.h
 *
 * Created On: 2020/12/07
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

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define DATA_PIN    3
#define BUTTON_PIN  4

#define NUM_LEDS    120

#define NUM_BYTES   3 * NUM_LEDS

#define UPDATE_FREQ 100

#endif
