#!/bin/bash

# Build the driver
cd src/driver
make

# Load Device Tree Overlay
sudo dtoverlay display.dtbo

# Load the kernel module
sudo insmod ssd1306_i2c.ko

cd ../..