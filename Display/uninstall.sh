#!/bin/bash

# Clean the build
cd src/driver
make clean

# Load Device Tree Overlay
sudo dtoverlay -R display

# Unload the kernel module
sudo rmmod ssd1306_i2c.ko

cd ../..