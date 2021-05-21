LED Strip Controller
==========================

Project Description:
---------------------
This project uses an Atmel ATtiny85 microcontroller to light up a strip of WS2812B LEDs with a set of 12 pre-defined patterns without relying on external libraries.

It is easy to create custom patterns as each LED is independently controlled.

A PCB design is included which allows the microcontroller and LED strip to be powered over a micro USB (type B) connection, with a toggle switch to turn the LED strip on or off and a Cherry-MX style button to cycle between the display modes.

Colors and Patterns:
---------------------

There are 12 pre-defined patterns programmed by default including 9 solid colors, an auto-cycle mode, disco mode and rainbow fade mode. The 9 pre-defined colors and their RGB hex values are as follows:

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

**Auto-cycle mode** cycles through the above solid colors in order from top to bottom, showing each color for a pre-defined time interval (currently set to 7s).

**Disco mode** gives each LED a random color from the above list (excluding white), which changes every 25ms.

**Rainbow fade mode** slowly transitions all LEDS in a cycle from red to green to blue to red (and so on).

The modes are cycled in the order they are listed in above, starting from solid red. When the toggle button is pressed in rainbow fade mode, the pattern will cycle back around to solid red.

Limitations:
-------------
Since the LED colors are programmed without an external library, the communication with the LED strip is done using a custom function written in assembly which determines the correct signal timing by counting clock cycles. The number of clock cycles required to send the correct data has been tuned for a 16MHz clock frequency and therefore in order to display the correct colors, 16MHz is the only frequency which may be used.

Each LED is given its own memory location which defines the RGB color components and allows each LED to be set independently. However, since the ATtiny85 contains only 512 bytes of SRAM then the number of LEDs which can be controlled by this MCU is limited. The controller program utilises 20 bytes of data memory leaving 492 bytes for RGB data and stack memory. The minimum stack size required is approximately 22 bytes and the RGB data consists of 3 bytes per LED meaning a maximum of 156 LEDs can be controlled with the ATtiny85 - more would require a microcontroller with more SRAM. This is enough to control a 2m strip with 60LEDs/m (120 LEDs total) or a 5m strip with 30LEDs/m (150 LEDs total) which are both commonly found configurations.

Depending on the number of LEDs used and the pattern being displayed, the total current draw can exceed 2A which may exceed the safe limits of cheaper USB cables. It is recommended to use a cable with a high current rating.

Equipment Used:
----------------
* [Jaycar's 2M Addressable LED Strip](https://www.jaycar.com.au/2m-rgb-led-strip-with-120-x-addressable-w2812b-rgb-leds-arduino-mcu-compatible-5v/p/XC4390) 
* [ATtiny85 DIP8](https://www.microchip.com/wwwproducts/en/ATtiny85)
* [Jaycar's ISP Programmer (USBasp)](https://www.jaycar.com.au/isp-programmer-for-arduino-and-avr/p/XC4627)

