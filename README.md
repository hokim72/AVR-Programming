## Test Board

#### [GENIUS KIT STARTER PACK](http://kocoafab.cc/product/genius)
#### ATmega328P pin mapping
![ATmega328P pin mapping](ATmega328P_vs_Arduino_pin_mapping.png)
#### [Arduino Schematic](https://github.com/NashMicro/NashDuino/tree/master/Nano)
#### Arduino Bootloader

Arduino/hardware/arduino/avr/bootloaders/optiboot from [Arduino](https://github.com/arduino-org/Arduino)(512Byte w/o eeprom support)

```
$ avrdude -p atmega328p -c usbasp -U flash:w:optiboot_atmega328.hex -U lfuse:w:0xff:m -U hfuse:w:0xd6:m -U efuse:w:0x05:m 
```

[optiboot_atmega328.hex](https://github.com/hokim72/AVR-Common/blob/master/optiboot/optiboot_atmega328.hex)(1KByte w/ eeprom support)

```
$ avrdude -p atmega328p -c usbasp -U flash:w:optiboot_atmega328.hex -U lfuse:w:0xff:m -U hfuse:w:0xd4:m -U efuse:w:0x05:m
```

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
