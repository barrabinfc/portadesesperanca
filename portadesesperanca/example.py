from pyomxplayer import OMXPlayer
from pprint import pprint

import RPi.GPIO as GPIO

import time
usleep = lambda x: time.sleep(x/1000000.0)


# Control a LED
#pins = {'door': 11,
#        'led': 18}
#GPIO.setup( pins['led'], GPIO.OUT)
#GPIO.output(pins['led'], False)

# Read a button
#GPIO.setup( pins['door'], GPIO.IN)

omx = OMXPlayer('/home/pi/raspberry-test.mp4', '-b -o hdmi --loop')
pprint(omx.__dict__)

# Door state tracking
#door_state = 0
#playing = False
omg.toggle_pause()
usleep( 100 )

while 1:
    print omx.position
    usleep( 100 )

    if omx.position <= 0.00:
        omx.toggle_pause()
        omx.position = 0.0
        omx.toggle_pause()

#    door_state = GPIO.input( pins['door'] )
#    if door_state == 1:             # OPEN
#        if not playing:
#            omg.position = 0.0
#            omx.play()
#            GPIO.output( pins['led'], True)
#            playing = True
#    else:                           # Closed
#        omx.pause()
