#!/bin/bash

# Clean the build
cd src/driver
make clean

# Load Device Tree Overlay
sudo dtoverlay -R motor

# Unload the kernel module
sudo rmmod dt_motor_i2c.ko

cd ../..