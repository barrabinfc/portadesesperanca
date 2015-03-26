#!/usr/bin/env python
# Simple script for shutting down the raspberry Pi at the press of a button.
# by Inderpreet Singh
 
import RPi.GPIO as GPIO
import time
import os
 
# Use the Broadcom SOC Pin numbers
# Setup the Pin with Internal pullups enabled and PIN in reading mode.
GPIO.setmode(GPIO.BCM)
GPIO.setup(16, GPIO.IN, pull_up_down = GPIO.PUD_UP)
 
# Our function on what to do when the button is pressed
def Shutdown(channel):
 print("Falling/RISING: %s " % (channel))
 
# Add our function to execute when the button pressed event happens
GPIO.add_event_detect(16, GPIO.BOTH, callback = Shutdown, bouncetime = 200)

#def Shutdown2(channel):
# print("on/OFF RISING")

## Add our function to execute when the button pressed event happens
#GPIO.add_event_detect(16, GPIO.RISING, callback = Shutdown2, bouncetime = 200)
 
# Now wait!
while 1:
 time.sleep(1)
