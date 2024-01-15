#!/bin/bash

# Build the driver
cd src/driver
make

# Load Device Tree Overlay
sudo dtoverlay motor.dtbo

# Load the kernel module
sudo insmod dt_motor_i2c.ko


cd ../..