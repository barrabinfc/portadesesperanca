from pyomxplayer import OMXPlayer
from pprint import pprint

import RPi.GPIO as GPIO

# Control a LED
#pins = {'door': 11,
#        'led': 18}
#GPIO.setup( pins['led'], GPIO.OUT)
#GPIO.output(pins['led'], False)

# Read a button
#GPIO.setup( pins['door'], GPIO.IN)

omx = OMXPlayer('/home/pi/earth.mp4')
pprint(omx.__dict__)

# Door state tracking
#door_state = 0
#playing = False

#while 1:
#    door_state = GPIO.input( pins['door'] )
#    if door_state == 1:             # OPEN
#        if not playing:
#            omg.position = 0.0
#            omx.play()
#            GPIO.output( pins['led'], True)
#            playing = True
#    else:                           # Closed
#        omx.pause()
#        playing = False

omx.toggle_pause()
omx.stop()
