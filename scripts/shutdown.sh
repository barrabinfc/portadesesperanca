#!/bin/bash
 
# monitor GPIO pin 31 (wiringPi pin 1) for shutdown signal
 
# export GPIO pin 31 and set to input with pull-up
echo "27" > /sys/class/gpio/export
echo "in" > /sys/class/gpio/gpio27/direction
echo "low" > /sys/class/gpio/gpio27/direction
 
# wait for pin to go low
while [ true ]
do
if [ "$(cat /sys/class/gpio/gpio27/value)" == '0' ]
then
 echo "on/OFF == 0!"
else
 echo "on/OFF == 1!"
fi

sleep 1
done
