.PHONY: all install dependencies

all: procfile auto_launch
	# type make install to install
	#
	#
procfile:
	echo 'Copying procfile'
	cp Procfile /home/pi/porta/
	
auto_launch:
	echo "--> Adding portadesesperanca launch script"
	cp -R scripts/* /home/pi/porta/scripts/
	cp -R scripts/rc.local /etc/rc.local
