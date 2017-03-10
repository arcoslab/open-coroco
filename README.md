open-coroco
===========

COmplaint RObot COntroller is a free software project aiming to create
an impedance controller based on a stm32 microcontroller using bldc
motors and strain gauges.

# Installation

## Requierments
Please install the following requierments according to your distribution/OS instructions:

- gcc-arm-none-eabi
- newlib for the toolchain
- stlink

libopencm3 is included as a git submodule

## Submodules
Init and download de submodules:
```bash
git submodule init
git submodule update
```
Compile them:
```bash
# libopencm3
cd libopencm3/
make

# libopencm3-plus
cd libopencm3-plus/
make
```
## Link motor header file

Because different motor require different parameters, we currently
have various motor header files in src/Configuration, in order to keep
things generic we currently link the header file to motor.h, for
example:

```bash
ln -s vexta_AXHM450KC-GFH.h motor.h
```

We are looking into a better way to do this.

## Generate trigonometric functions tables
Because of performance concerns we use tables to calculate
trigonometric functions, to generate the tables there are some python
2 scripts in src/Trigonometric_Functions/. You must provide the number
of elements on the table as a paremeter for this scripts and they
generate some c header files, for example:

```bash
python2 sine_table_generator.py 30
```
