#!/bin/bash

# # Build the driver
# cd src/driver
# make

# # Load Device Tree Overlay
# sudo dtoverlay gpio.dtbo

# # Load the kernel module
# sudo insmod GPIO_Driver.ko


# sudo echo "
# [Unit]
# Description=GPIO device tree overlay for the egg breeding machine
# After=DisplayDriver.service

# [Service]
# Type=oneshot
# ExecStart=dtoverlay $(pwd)/gpio.dtbo

# [Install]
# WantedBy=multi-user.target
# " > /etc/systemd/system/GPIODTO.service
# sudo systemctl daemon-reload
# sudo systemctl enable GPIODTO.service

# sudo echo "
# [Unit]
# Description=GPIO driver for the egg breeding machine
# After=GPIODTO.service

# [Service]
# Type=oneshot
# ExecStart=/sbin/insmod $(pwd)/GPIO_Driver.ko

# [Install]
# WantedBy=multi-user.target
# " > /etc/systemd/system/GPIODriver.service
# sudo systemctl daemon-reload
# sudo systemctl enable GPIODriver.service

# cd ../..