# Nexa remote control

Hardware and firmware for creating custom Nexa remote control. This project uses ATtiny85 and a STX882 ASK module as the RF module. It can be used to control various Nexa devices that uses 433 MHz.

One of the goals was to minimize the power usage so that it can run from a battery like CR2032.

![Final circuit](https://raw.githubusercontent.com/perja12/nexa_remote_control/master/hardware/final_circuit.jpg | width=250)

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

![Schematic](https://raw.githubusercontent.com/perja12/nexa_remote_control/master/hardware/schematic.jpg)

![Board](https://raw.githubusercontent.com/perja12/nexa_remote_control/master/hardware/board.jpg)

The RF module used here is https://www.aliexpress.com/item/10pcs-lot-ASK-RF-module-433mhz-transmitter-module/32238392004.html

# Resources
* Nexa devices: https://www.nexa.se/vara-produkter/system-nexa/mottagare-paav
* Pin change interrupt on ATtiny85:
    * https://thewanderingengineer.com/2014/08/11/pin-change-interrupts-on-attiny85/
    * https://embeddedthoughts.com/2016/06/06/attiny85-introduction-to-pin-change-and-timer-interrupts/
    * http://gammon.com.au/interrupts
* ATtiny85 datasheet: http://www.atmel.com/images/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf
* NexaCtrl library: https://github.com/calle-gunnarsson/NexaCtrl

# How to pair with a Nexa device

In order to use the controller with a device (like a plug-in receiver) you need to either find the existing id of your device and use that in `CONTROLLER_ID`. Or you can configure the device to listen for the id set in `CONTROLLER_ID` (self learning). Disconnect the device from mains and then plug it back in. Then, within 5 seconds, press the "on" button on the controller. You should then hear the relay switching a couple of times. If nothing happens, the device memory can be full and you have to reset it with a "group off" command during that 5 seconds start up. You probably have to do this with a paired remote. Consult the user manual of the device.

# Questions or found a bug?

Please raise an [issue](https://github.com/perja12/nexa_remote_control/issues/new) or a new [pull request](https://github.com/perja12/nexa_remote_control/pulls) if you have some code changes.
