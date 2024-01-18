#!/bin/bash

# Clean the build
cd src/driver
make clean

# Load Device Tree Overlay
sudo dtoverlay -R gpio

# Unload the kernel module
sudo rmmod GPIO_Driver

cd ../..