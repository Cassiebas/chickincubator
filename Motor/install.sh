#!/bin/bash

# Build the driver
cd src/driver
make

# Load Device Tree Overlay
sudo dtoverlay motor.dtbo

# Load the kernel module
sudo insmod dt_motor_i2c.ko

sudo echo "
[Unit]
Description=Motor device tree overlay for the egg breeding machine
After=network.target

[Service]
Type=oneshot
ExecStart=dtoverlay $(pwd)/motor.dtbo

[Install]
WantedBy=multi-user.target
" > /etc/systemd/system/MotorDTO.service
sudo systemctl daemon-reload
sudo systemctl enable MotorDTO.service

sudo echo "
[Unit]
Description=Motor driver for the egg breeding machine
After=MotorDTO.service

[Service]
Type=oneshot
ExecStart=/sbin/insmod $(pwd)/dt_motor_i2c.ko

[Install]
WantedBy=multi-user.target
" > /etc/systemd/system/MotorDriver.service
sudo systemctl daemon-reload
sudo systemctl enable MotorDriver.service


cd ../..