#!/bin/bash

# Build the driver
cd src/driver
make

# Load Device Tree Overlay
sudo dtoverlay display.dtbo

# Load the kernel module
sudo insmod ssd1306_i2c.ko

sudo echo "
[Unit]
Description=Display device tree overlay for the egg breeding machine
After=MotorDriver.service

[Service]
Type=oneshot
ExecStart=dtoverlay $(pwd)/display.dtbo

[Install]
WantedBy=multi-user.target
" > /etc/systemd/system/DisplayDTO.service
sudo systemctl daemon-reload
sudo systemctl enable DisplayDTO.service

sudo echo "
[Unit]
Description=Display driver for the egg breeding machine
After=DisplayDTO.service

[Service]
Type=oneshot
ExecStart=/sbin/insmod $(pwd)/ssd1306_i2c.ko

[Install]
WantedBy=multi-user.target
" > /etc/systemd/system/DisplayDriver.service
sudo systemctl daemon-reload
sudo systemctl enable DisplayDriver.service

cd ../..