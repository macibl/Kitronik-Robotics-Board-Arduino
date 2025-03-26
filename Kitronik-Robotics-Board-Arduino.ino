# Use a Kitronik Robotics board with Arduino language
# Note : Kitronik Robotics board is designed to use a Raspberry Pi Pico module, 
#        but any microcontroller module with an I2C interface can be used.
# Restrictions: only motors can be controlled
# 
# based on https://github.com/KitronikLtd/Kitronik-Pico-Robotics-Board-MicroPython/blob/main/PicoRobotics.py
#
#include <Arduino.h>
#include <PCA9685.h>
