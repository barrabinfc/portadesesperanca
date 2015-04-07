#!/bin/bash

export PATH=$PATH:$(pwd)/scripts

MOVIE=/home/pi/porta/movies/kinoplex.mp4

omxplayer --loop -I --blank --pos 0 -o hdmi $MOVIE &
