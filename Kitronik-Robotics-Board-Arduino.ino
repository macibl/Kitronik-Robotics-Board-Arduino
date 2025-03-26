# Use a Kitronik Robotics board with Arduino language
# Note : Kitronik Robotics board is designed to use a Raspberry Pi Pico module, 
#        but any microcontroller module with an I2C interface can be used.
# Restrictions: only motors can be controlled
# First use of this file : use only one motor, forward, at low speed and stop it after a few seconds

# based on official library for Kitronik Robotics Board Pico in MicroPython language here:
#    https://github.com/KitronikLtd/Kitronik-Pico-Robotics-Board-MicroPython/blob/main/PicoRobotics.py
#

#include PicoRobotics.h"

