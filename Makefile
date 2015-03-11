.PHONY: all install dependencies

all:
	# type make install to install

install: dependencies
	echo "installed"

bootstrap_user:
	mkdir -p /home/porta
	usermod -aG root porta

dependencies:
	echo "--> Running apt-get update"
	sudo apt-get update > /dev/null
	echo "--> Installing python-pip"
	sudo apt-get install python-pip
	echo "--> Installing python dependencies"
	sudo pip install -r requirements.txt
	sudo python pyomxplayer/setup.py install
