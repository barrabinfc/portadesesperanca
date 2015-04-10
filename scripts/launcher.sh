#!/bin/bash

PATH=/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games
ROOT_P=/home/pi/porta/ 

cd $ROOT_P; procman start;
sleep 5;
RC=1

while [ true ]; do
    { 
        cd $ROOT_P && ./scripts/dbus.sh status >> $ROOT_P/seguranca.txt;
    } || {
        cd $ROOT_P && echo 'FUdEU; restart! ' >> $ROOT_P/seguranca.txt;
        cd $ROOT_P && procman restart;
    }
    sleep 3;
done

