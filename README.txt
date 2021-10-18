##################
# General Instructions
##################

- apt-get install build-essential liblapack-dev libboost-all-dev libusb-1.0-0-dev
- download http://www.xsens.com/download/MT/4.2.1/mfmsdk_mtm_mtsdk_linux_4.2.1_beta.zip
- extract and cd to mtsdk/shared_object/
- edit serialkey.h: insert 485DA-A98ED-FA73E-803E9
- sudo make system_install
- make all
- create 10-xsens.rules in /etc/udev/rules.d/ with the following content:
#-------------------------------------------------------------------------------------------------------
# Xsens
#
SUBSYSTEMS=="usb", KERNEL=="ttyUSB*", ATTRS{manufacturer}=="Xsens", RUN+="/bin/sh -c 'echo 2 > /sys/class/tty/$KERNEL/device/latency_timer'"
#
#-------------------------------------------------------------------------------------------------------

- reboot
- test functionality with sudo ./example_mt_w_cpp 

- in order to use the xsens-library as a user, you have to add the user to the dialout group
  sudo adduser yourUsername dialout

##################
# Usage with Ubuntu 14.10.
##################
- If you use ubuntu 14.10., you need to downgrade your gcc and/or g++ compiler version to 4.8 to compile teh xsens examples
- remove old version: 
  sudo apt-get remove gcc g++
- install new version
  sudo apt-get install gcc-4.8 g++-4.8
- link new versions
  sudo ln -s /usr/bin/gcc-4.8 /usr/bin/gcc
  sudo ln -s /usr/bin/g++-4.8 /usr/bin/g++