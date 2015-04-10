.PHONY: all install dependencies

all: procfile auto_launch 
	# type make install to install
	#
install:
	sudo dpkg -i misc/omxplayer_0.3.6~git20150402~74aac37_armhf.deb
	#cp misc/3x/*.mov /home/pi/porta/movies/3x

procfile:
	echo 'Copying procfile'
	cp Procfile /home/pi/porta/
	
auto_launch:
	echo "--> Adding portadesesperanca launch script"
	cp -R scripts/* /home/pi/porta/scripts/
	cp -R scripts/rc.local /etc/rc.local
	sudo cp -R scripts/boot_config.txt /boot/config.txt

	echo 'Edit ~/porta/scripts/omxp.sh / ~/porta/scripts/genius.sh'
