#/bin/bash

#install needed packages
sudo apt-get update
sudo apt-get -y upgrade
sudo apt-get -y install gnuplot libgnuplot-iostream-dev libboost-all-dev nginx

#install drivers and build c++ program
cd Display/
./install.sh
cd ../Motor/
./install.sh
cd ../GPIO/
./install.sh
cd ../
make

#make drivers and c++ program start on boot:
sudo cp install/DisplayDTO.service /etc/systemd/system/DisplayDTO.service
sudo systemctl daemon-reload
sudo systemctl enable DisplayDTO.service

sudo cp install/DisplayDriver.service /etc/systemd/system/DisplayDriver.service
sudo systemctl daemon-reload
sudo systemctl enable DisplayDriver.service

sudo cp install/GPIODriver.service /etc/systemd/system/GPIODriver.service
sudo systemctl daemon-reload
sudo systemctl enable GPIODriver.service

sudo cp install/MotorDTO.service /etc/systemd/system/MotorDTO.service
sudo systemctl daemon-reload
sudo systemctl enable MotorDTO.service

sudo cp install/MotorDriver.service /etc/systemd/system/MotorDriver.service
sudo systemctl daemon-reload
sudo systemctl enable MotorDriver.service

sudo cp install/EggIncubator.service /etc/systemd/system/EggIncubator.service
sudo systemctl daemon-reload
sudo systemctl enable EggIncubator.service

#nginx setup:
sudo mkdir /var/www/eggcubator
sudo cp install/index.html /var/www/eggcubator/index.html
sudo cp install/default /etc/nginx/sites-available/default
sudo systemctl restart nginx