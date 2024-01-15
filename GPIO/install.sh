#!/bin/bash

# Build the driver
cd src/driver
make

# Load the kernel module
sudo insmod GPIO_Driver.ko

# Set permissions on the device file
sudo chmod 666 /dev/gpio_driver_egg_incubator


cd ../..