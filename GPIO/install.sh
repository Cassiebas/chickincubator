#!/bin/bash

# Build the driver
cd src/driver
make

# Load the kernel module
sudo insmod GPIO_Driver.ko

# Set permissions on the device file
sudo chmod 666 /dev/gpio_driver_egg_incubator

sudo echo "
[Unit]
Description=GPIO driver for the egg breeding machine
After=DisplayDriver.service

[Service]
Type=oneshot
ExecStart=/sbin/insmod $(pwd)/GPIO_Driver.ko

[Install]
WantedBy=multi-user.target
" > /etc/systemd/system/GPIODriver.service
sudo systemctl daemon-reload
sudo systemctl enable GPIODriver.service

cd ../..