.PHONY: all install dependencies

all:
	# type make install to install

install: dependencies
	echo "installed"

dependencies:
	echo "--> Installing python-pip"
	sudo apt-get install python-pip
	sudo pip install RPi.GPIO

auto_launch:
	echo "--> Adding portadesesperanca to ~/.bashrc"
	echo '/home/pi/portadesesperanca/launcher.sh' >> ~/.bashrc
