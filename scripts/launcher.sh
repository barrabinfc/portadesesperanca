#!/bin/bash

PATH=/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games
ROOT_P=/home/pi/porta/ 

RC=1
while [ $RC -ne 0 ]; do
    cd $ROOT_P; procman restart
    RC=$?
done

