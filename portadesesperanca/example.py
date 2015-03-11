#!/usr/bin/env python
from pyomxplayer import OMXPlayer
from pprint import pprint

import RPi.GPIO as GPIO

import time, os
usleep = lambda x: time.sleep(x/1000000.0)

import signal
import sys
def signal_handler(signal, frame):
        print('You pressed Ctrl+C!')
        sys.exit(0)
signal.signal(signal.SIGINT, signal_handler)
print('Press Ctrl+C to stop')

# Control a LED
#pins = {'door': 11,
#        'led': 18}
#GPIO.setup( pins['led'], GPIO.OUT)
#GPIO.output(pins['led'], False)

# Read a button
#GPIO.setup( pins['door'], GPIO.IN)

loop1 = OMXPlayer('/home/pi/raspberry-test.mp4', '-b -o hdmi')
loop2 = OMXPlayer('/home/pi/earth.mp4','-b -o hdmi')
pprint(loop1.__dict__)
pprint(loop2.__dict__)

loop2.toggle_pause()

# Door state tracking
#door_state = 0
#playing = False

while 1:
    position = loop1.position/1000000 
    position2 = loop2.position/1000000
    print position
    if position > 12.8:      
        self.loop1.toggle_pause() 
        self.loop2.toggle_pause()

        sleep(2) 
        os.system('pkill -9 -f "/usr/bin/omxplayer.bin -s /home/pi/raspberry-test.mp4 -b -o hdmi "') 
        os.system('pkill -9 -f "/bin/bash /usr/bin/omxplayer -s /home/pi/raspberry-test.mp4 -b -o hdmi"')
        sleep(2)

        loop1 = OMXPlayer('/home/pi/raspberry-test.mp4', '-o local', start_playback=True, do_dict=False) 
        loop1.toggle_pause() 

#    door_state = GPIO.input( pins['door'] )
#    if door_state == 1:             # OPEN
#        if not playing:
#            omg.position = 0.0
#            omx.play()
#            GPIO.output( pins['led'], True)
#            playing = True
#    else:                           # Closed
#        omx.pause()
