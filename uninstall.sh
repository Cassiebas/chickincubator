#/bin/bash

cd Display/
./uninstall.sh
cd ../Motor/
./uninstall.sh
cd ../GPIO/
./uninstall.sh
cd ../
make clean
sudo systemctl stop EggIncubator
sudo systemctl stop GPIODTO
sudo systemctl stop GPIODriver
sudo systemctl stop DisplayDTO
sudo systemctl stop DisplayDriver
sudo systemctl stop MotorDTO
sudo systemctl stop MotorDriver
sudo rm -f /etc/systemd/system/EggIncubator.service
sudo rm -f /etc/systemd/system/GPIODTO.service
sudo rm -f /etc/systemd/system/GPIODriver.service
sudo rm -f /etc/systemd/system/DisplayDTO.service
sudo rm -f /etc/systemd/system/DisplayDriver.service
sudo rm -f /etc/systemd/system/MotorDTO.service
sudo rm -f /etc/systemd/system/MotorDriver.service