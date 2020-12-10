LED Strip Controller
==========================
Author: Aaron Lucas

Date Created: 2020/12/02

Project Description:
---------------------
This project uses an Atmel ATtiny85 microcontroller to light up a strip of WS2812B LEDs with a set of pre-defined patterns which can be used for decoration, without relying on external libraries.

The code can be modified to fully control the color of each LED without.

A push-button connected to the MCU allows a collection of 12 patterns to be cycled through, which include 9 solid colors, an auto-cycle mode, a disco mode and a rainbow fade mode.

Colors and Patterns:
---------------------

The 9 pre-defined colors and their RGB hex values are as follows:

    * Red               [0xC00000]
    * Green             [0x206000]
    * Purple            [0x6E00FF]
    * Orange            [0xFF2000]
    * Blue              [0x001080]
    * White             [0x867565]
    * Pink              [0xFF009A]
    * Yellow            [0xEA5200]
    * Light blue/cyan   [0x00777A]

Theoretically, some of these colors are inaccurate (e.g. the RGB combination for yellow is actually orange), however due to the different intensities of the individual red, green and blue LEDs, these color definitions show the correct color when displayed on the WS2812B LED strip.

**Auto-cycle mode** cycles through the above solid colors in order from top to bottom, showing each color for a pre-defined time interval.

**Disco mode** gives each LED a random color from the above list (excluding white), which changes every 100ms.

**Rainbow fade mode** slowly transitions all LEDS in a cycle from red to green to blue to red (and so on).

Limitations:
-------------
Since the LED colors are programmed without an external library, the communication with the LED strip is done using a custom function written in assembly which determines the correct signal timing by counting clock cycles. The number of clock cycles required to send the correct data has been tuned for a 16MHz clock frequency and therefore in order to display the correct colors, 16MHz is the only frequency which may be used.

Each LED is given its own memory location which defines the RGB color components and allows each LED to be set independently. However, since the ATtiny85 contains only 512 bytes of SRAM then the number of LEDs which can be controlled by this MCU is limited. The controller program utilises 57 bytes of data memory leaving 455 bytes for RGB data, which consists of 3 bytes per LED. Thus, a maximum of 151 LEDs can be controlled with the ATtiny85 - more would require a microcontroller with more SRAM.

Equipment Used:
----------------
    * [Jaycar's 2M Addressable LED Strip](https://www.jaycar.com.au/2m-rgb-led-strip-with-120-x-addressable-w2812b-rgb-leds-arduino-mcu-compatible-5v/p/XC4390) 
    * [ATtiny85 DIP8](https://www.microchip.com/wwwproducts/en/ATtiny85)
    * [Jaycar's ISP Programmer (USBasp)](https://www.jaycar.com.au/isp-programmer-for-arduino-and-avr/p/XC4627)

