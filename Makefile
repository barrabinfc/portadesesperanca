.PHONY: all install dependencies

all:
	# type make install to install
	#
run:
	sudo portadesesperanca/bin/portadesesperanca

install: auto_launch
	echo "--> Copying porta binary"
	cp -R portadesesperanca/bin/* /home/pi/porta/bin

dependencies:
	echo "--> Installing python-pip"
	sudo apt-get install python-pip
	sudo pip install RPi.GPIO

auto_launch:
	echo "--> Adding portadesesperanca launch script"
	cp scripts/launcher.sh /home/pi/porta/scripts/
