#!/bin/bash
 
# export GPIO pin 16 and set to input with pull-up
echo "16" > /sys/class/gpio/export
echo "in" > /sys/class/gpio/gpio16/direction
echo "low" > /sys/class/gpio/gpio16/direction
 
# wait for pin to go low
while [ true ]
do
if [ "$(cat /sys/class/gpio/gpio16/value)" == '0' ]
then
 echo "on/OFF == 0!"
else
 echo "on/OFF == 1!"
fi

done
