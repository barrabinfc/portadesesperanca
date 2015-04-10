#!/bin/bash

export PATH=$PATH:$(pwd)/scripts

MOVIE=/home/pi/porta/movies/3x/vlmadalena3x.mov

NOREFRESH=1 omxplayer --no-osd --orientation 90 -z -I --blank --loop --no-keys -o hdmi --genlog $MOVIE &
#omxplayer --refresh -I --blank --loop --no-keys -o hdmi --genlog $MOVIE &
