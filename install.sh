#/bin/bash

#install needed packages
# sudo apt-get update
# sudo apt-get -y upgrade
# sudo apt-get -y install gnuplot libgnuplot-iostream-dev libboost-all-dev nginx

#install drivers and build c++ program

cd Motor/
sudo ./install.sh
cd ../Display/
sudo ./install.sh
cd ../GPIO/
sudo ./install.sh
cd ../
make

sudo echo "
[Unit]
Description=Egg breeding machine
After=GPIODriver.service

[Service]
ExecStart=$(pwd)/bin/EggIncubator
WorkingDirectory=$(pwd)/bin
StandardOutput=inherit
StandardError=inherit
Restart=always
User=pi

[Install]
WantedBy=multi-user.target
" > /etc/systemd/system/EggIncubator.service
sudo systemctl daemon-reload
sudo systemctl enable EggIncubator.service

#nginx setup:
sudo mkdir /var/www/eggcubator
sudo cp install/index.html /var/www/eggcubator/index.html
sudo cp install/default /etc/nginx/sites-available/default
sudo systemctl restart nginx