#/bin/bash

cd Display/
./uninstall.sh
cd ../Motor/
./uninstall.sh
cd ../GPIO/
./uninstall.sh
cd ../
make clean
sudo systemctl stop /etc/systemd/system/EggIncubator.service
sudo systemctl stop /etc/systemd/system/GPIODriver.service
sudo systemctl stop /etc/systemd/system/DisplayDTO.service
sudo systemctl stop /etc/systemd/system/DisplayDriver.service
sudo systemctl stop /etc/systemd/system/MotorDTO.service
sudo systemctl stop /etc/systemd/system/MotorDriver.service
sudo rm -f /etc/systemd/system/EggIncubator.service
sudo rm -f /etc/systemd/system/GPIODriver.service
sudo rm -f /etc/systemd/system/DisplayDTO.service
sudo rm -f /etc/systemd/system/DisplayDriver.service
sudo rm -f /etc/systemd/system/MotorDTO.service
sudo rm -f /etc/systemd/system/MotorDriver.service