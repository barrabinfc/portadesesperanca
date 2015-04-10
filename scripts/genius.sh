#!/bin/bash

export PIN=27;
export PATH=$PATH:$(pwd)/scripts

echo "Path is: $PATH"
echo "REading sensor from port (wiringPI) $PIN "

# pin 27 (36)
gpio export $PIN in
gpio mode $PIN up

gpio readall

export RASP_ID="kinoplex bkp"
echo "LAUNCHING: $RASP_ID $(date '+%d/%m/%y %H:%M:%S')" >> /home/pi/porta/doormetrics.txt

last_door_status='1';

while [ true ]; do
    door_open=$(gpio read $PIN)

    if [ $door_open == $last_door_status ];then
        continue;
    else
        if [ $door_open == '0' ];then
         { 
            dbus.sh setposition 0; sleep 0.01; dbus.sh pause;
         } || { 
            pkill -9 omxplayer;
         }
         echo "$(date '+%d/%m/%y %H:%M:%S') DOOR_CLOSED" >> /home/pi/porta/doormetrics.txt
         echo "porta FECHADA!";
        else
         { 
             dbus.sh pause;
         } || { 
            pkill -9 omxplayer;
         }
         echo "$(date '+%d/%m/%y %H:%M:%S') DOOR_OPENED" >> /home/pi/porta/doormetrics.txt
         echo "porta ABERTA";
        fi
        last_door_status=$door_open;
    fi;

done;
