/* ============================================================================
 * LED Strip Controller - ATtiny85 MCU-based control of WS2812B LED Strips.
 *
 * main.c
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

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "definitions.h"
#include "rgb_data.h"
#include "patterns.h"

// Setup functions
static void setup_gpio(void);
static void setup_pattern_timer(void);

// Function written in assembly to provide precise timings
extern void update_leds(struct rgb_data *colors);

// Collection of LED byte data
static struct rgb_data led_buffer[NUM_LEDS] = { 0 };
static inline void set_led(uint8_t led, enum color c) {
    led_buffer[led] = get_rgb(c);
}

static volatile enum pattern led_pattern;
static void show_next_pattern(void);

int main(void) {
    // Hardware setup
    cli();
    setup_gpio();
    setup_pattern_timer();
    sei();

    // Set initial state to first color in cycle
    led_pattern = FIRST_PATTERN;
    update_pattern(led_buffer, led_pattern, true);

    // Poll for buton press
    uint8_t btn_state_cur = 0, btn_state_prev = 0;
    while (1) {
        // Read current state and check for rising edge
        btn_state_cur = PINB & (1 << BUTTON_PIN);
        if (btn_state_cur && !btn_state_prev) {
            show_next_pattern();
        }
        btn_state_prev = btn_state_cur;

        // Debouncing delay
        _delay_ms(5);
    }
}

static void setup_gpio(void) {
    DDRB |= (1 << DATA_PIN);  // Set data pin to output

    DDRB &= ~(1 << BUTTON_PIN);  // Set button pin to input
    PORTB &= ~(1 << BUTTON_PIN); // Disable pull-up resistor
}

static void setup_pattern_timer(void) {
    // Interrupt every 10ms (100Hz)
    // 157 * 1024 / 16e6 = 10.048ms
    TCNT1 = 0;                              // Start counting from 0
    OCR1A = 157;                            // Counting to 157 takes 10ms
    OCR1C = OCR1A;                          // CTC mode uses OCR1C
    TIMSK |= (1 << OCIE1A);                 // Interrupt uses OCR1A
    TCCR1 |= ((1 << CTC1) | (0xB << CS10)); // CTC Mode with 1024x prescaler
}

static void show_next_pattern(void) {
    if (++led_pattern == NUM_PATTERNS) {
        led_pattern = FIRST_PATTERN;
    }

    // Cycle to next pattern, starting cycles from the start
    update_pattern(led_buffer, led_pattern, true);
}

ISR(TIMER1_COMPA_vect) {
    // Don't reset cycle patterns from the start
    update_pattern(led_buffer, led_pattern, false);
    update_leds(led_buffer);
}
