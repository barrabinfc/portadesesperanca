.PHONY: all install dependencies

all:
	# type make install to install

install: dependencies
	echo "installed"

dependencies:
	echo "--> Running apt-get update"
	sudo apt-get update > /dev/null
	echo "--> Installing python-pip"
	sudo apt-get install python-pip
	echo "--> Installing python package "
	python setup.py install
	#git clone https://github.com/jbaiter/pyomxplayer.git
	#python pyomxplayer/setup.py install
