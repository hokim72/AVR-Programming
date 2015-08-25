## Test Board

#### [GENIUS KIT STARTER PACK](http://kocoafab.cc/product/genius)
#### ATmega328P pin mapping
![ATmega328P pin mapping](ATmega328P_vs_Arduino_pin_mapping.png)
#### [Arduino Schematic](https://www.arduino.cc/en/uploads/Main/ArduinoNano30Schematic.pdf)
#### Arduino Bootloader
Arduino/hardware/arduino/avr/bootloaders/optiboot from [Arduino](https://github.com/arduino-org/Arduino)
#### [Fuse settings](http://www.martyncurrey.com/arduino-atmega-328p-fuse-settings/)
#### [Lock bits](http://www.avrfreaks.net/forum/lock-bits-1)
#### [Fuse calculator](http://eleccelerator.com/fusecalc/fusecalc.php?chip=atmega328p)
#### [Bootloader setting with avrdude](http://www.hackersworkbench.com/intro-to-bootloaders-for-avr)

## Prerequisite

#### [AVR-Common](https://github.com/hokim72/AVR-Common)

## Compile and build

```
$ cd ~/work/avr
$ git clone https://github.com/hokim72/AVR-Programming.git
$ mkdir AVR-Programming/project_dir/build; cd AVR-Programming/project_dir/build
$ cmake-avr ..
$ make flash
```

## AVR USB Bootloader

#### [USnoobie Kit](http://www.seeedstudio.com/wiki/Usnoobie_Kit)
#### [HID-class USB Serial Communication for AVRs using V-USB](http://rayshobby.net/hid-class-usb-serial-communication-for-avrs-using-v-usb/)

## AVR Definitions and Functions

#### [busy-wait delay loops](http://www.nongnu.org/avr-libc/user-manual/group__util__delay.html)
