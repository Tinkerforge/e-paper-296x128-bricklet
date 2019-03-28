#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_e_paper_296x128'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XYZ' # Change XYZ to the UID of your E-Paper 296x128 Bricklet

ipcon = IPConnection.new # Create IP connection
ep = BrickletEPaper296x128.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Use black background
ep.fill_display BrickletEPaper296x128::COLOR_BLACK

# Write big white "Hello World" in the middle of the screen
ep.draw_text 16, 48, BrickletEPaper296x128::FONT_24X32, \
             BrickletEPaper296x128::COLOR_WHITE, \
             BrickletEPaper296x128::ORIENTATION_HORIZONTAL, 'Hello World'
ep.draw

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
