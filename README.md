# Nexa remote control

Hardware and firmware for creating custom Nexa remote control. This project uses ATtiny85 and a STX882 ASK module as the RF module. It can be used to control various Nexa devices that uses 433 MHz.

One of the goals was to minimize the power usage so that it can run from a battery like CR2032.

## Installing NexaCtrl library

The firmware uses the NexaCtrl library and this be installed in your Arduino folder:
```bash
cd ~/Arduino/libraries
git clone git@github.com:calle-gunnarsson/NexaCtrl.git
```

## Building the firmware and uploading it to ATtiny85

To build the firmware, use the provided Makefile:
```bash
make
```

This project uses an Arduino Uno to program the ATtiny85:
https://create.arduino.cc/projecthub/arjun/programming-attiny85-with-arduino-uno-afb829

Once you have the setup ready you can upload the firmware with the command:
```bash
make upload
```

# Hardware

See the hardware folder for schematic and board layout files from Eagle. And also the list of parts. Note that it can use either a coin cell battery (CR2032) or f.ex. 2xAA batteries connected to the battery terminal.

![Schematic](https://raw.githubusercontent.com/perja12/nexa_remote_control/hardware/master/schematic.png)

![Board](https://raw.githubusercontent.com/perja12/nexa_remote_control/hardware/master/board.png)

# Resources
* Nexa devices: https://www.nexa.se/vara-produkter/system-nexa/mottagare-paav
* Pin change interrupt on ATtiny85:
** https://thewanderingengineer.com/2014/08/11/pin-change-interrupts-on-attiny85/
** https://embeddedthoughts.com/2016/06/06/attiny85-introduction-to-pin-change-and-timer-interrupts/
** http://gammon.com.au/interrupts
* ATtiny85 datasheet: http://www.atmel.com/images/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf
* NexaCtrl library: https://github.com/calle-gunnarsson/NexaCtrl
