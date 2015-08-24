## Test Board

#### [GENIUS KIT STARTER PACK](http://kocoafab.cc/product/genius)
#### ATmega328P pin mapping
![ATmega328P pin mapping](ATmega328P_vs_Arduino_pin_mapping.png)
#### [Arduino Schematic](https://www.arduino.cc/en/uploads/Main/Arduino_Uno_Rev3-schematic.pdf)
#### Arduino Bootloader
Arduino/hardware/arduino/avr/bootloaders/optiboot from [Arduino](https://github.com/arduino-org/Arduino)
#### [Loading an Arduino Bootloader](http://blog.allthingsgeek.com/article/index/index/id/27#.VdWlNXWlxBc)

## AVRDUDE

```
$ wget https://copr-be.cloud.fedoraproject.org/results/jlindeberg/arduino-epel7/epel-7-x86_64/avrdude-6.1-2.fc22/avrdude-6.1-2.el7.centos.x86_64.rpm
$ sudo yum install libftdi
$ sudo rpm -ivh avrdude-6.1-2.el7.centos.x86_64.rpm
$ sudo usermod -a -G dialout hokim
```

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

#### [AVR Bootloader](http://www.electroschematics.com/10778/avr-bootloader/)
#### [Working With Bootloaders & Build Your Own Bootloader – 1](http://www.electroschematics.com/10850/working-bootloaders-build-bootloader-1/)
#### [Working With Bootloaders & Build Your Own Bootloader – 2](http://www.electroschematics.com/10922/working-bootloaders-build-bootloader-2/)

## AVR Definitions and Functions

#### [busy-wait delay loops](http://www.nongnu.org/avr-libc/user-manual/group__util__delay.html)
