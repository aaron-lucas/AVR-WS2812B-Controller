; ============================================================================
; LED Strip Controller - ATtiny85 MCU-based control of WS2812B LED Strips.
; 
; update_leds.S
; Encode the LED color data using the WS2812B NZR protocol and send it to the
; LED strip.
; 
; Created On: 2020/12/07
; 
; Copyright (C) 2020  Aaron Lucas
; 
; This program is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.
; 
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
; 
; You should have received a copy of the GNU General Public License
; along with this program.  If not, see <https://www.gnu.org/licenses/>.
; 
; aaronlucas98@gmail.com
; https://github.com/aaron-lucas
; ============================================================================

#include		"definitions.h"

#define			bit_count	r18
#define			byte_to_send	r19
#define			reset_counter	r20
#define			sreg_save	r21

#define			byte_count_l	r24
#define			byte_count_h	r25
#define			p_colors	r24

#define			byte_addr_l	r30
#define			byte_addr_h	r31

.equ			SREG,		0x3F
.equ			PORTB,		0x18

.text

.global			update_leds
	.type		update_leds, @function
update_leds:
			in	sreg_save, SREG				; Preserve status register
			movw	byte_addr_l, p_colors
			ldi	byte_count_l, lo8(NUM_BYTES+1)
			ldi	byte_count_h, hi8(NUM_BYTES+1)
			ldi	reset_counter, 200

reset_loop:		
			nop
			nop
			dec	reset_counter
			brne	reset_loop

; Hold DATA_PIN for 7cc, set HIGH for 4/5cc (bit = 0/1 respectively)
load_byte:
		       	sbiw	byte_count_l, 1
		       	breq	finished
		       	ld	byte_to_send, Z+
		       	sbi	PORTB,	DATA_PIN
		       	ldi	bit_count, 8
		       	rol	byte_to_send
		       	brcc	send_0
			rjmp	send_1

; Hold DATA_PIN for 2cc, set LOW for 9cc (3cc if loading new byte)
send_0:
		       	cbi	PORTB,	DATA_PIN
		       	dec	bit_count
		       	breq	load_byte
			nop
			nop
			nop
			nop
		       	nop
			rjmp	send_common

; Hold DATA_PIN for 8cc, set LOW for 2cc (3cc if loading new byte)
send_1:
			nop
			nop
			nop
			nop
			nop
		       	nop
		       	cbi	PORTB,	DATA_PIN
		       	dec	bit_count
			breq	load_byte

; Hold DATA_PIN for 5cc, set HIGH for 4/5cc (bit = 0/1 respectively
send_common:
		       	nop
		       	nop
		       	nop
		       	sbi	PORTB,	DATA_PIN
		       	nop
		       	rol	byte_to_send
		       	brcc	send_0
		       	rjmp	send_1

finished:
			out	SREG, sreg_save				; Restore status register
		       	ret
