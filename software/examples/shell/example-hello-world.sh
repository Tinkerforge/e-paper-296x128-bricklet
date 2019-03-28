#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your E-Paper 296x128 Bricklet

# Use black background
tinkerforge call e-paper-296x128-bricklet $uid fill-display color-black

# Write big white "Hello World" in the middle of the screen
tinkerforge call e-paper-296x128-bricklet $uid draw-text 16 48 font-24x32 color-white orientation-horizontal "Hello World"
tinkerforge call e-paper-296x128-bricklet $uid draw
