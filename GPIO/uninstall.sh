#!/bin/bash

# Clean the build
cd src/driver
make clean

# Unload the kernel module
sudo rmmod GPIO_Driver

cd ../..