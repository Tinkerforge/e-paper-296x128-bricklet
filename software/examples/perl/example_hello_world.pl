#!/usr/bin/perl

use strict;
use Tinkerforge::IPConnection;
use Tinkerforge::BrickletEPaper296x128;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change XYZ to the UID of your E-Paper 296x128 Bricklet

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $ep = Tinkerforge::BrickletEPaper296x128->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Use black background
$ep->fill_display($ep->COLOR_BLACK);

# Write big white "Hello World" in the middle of the screen
$ep->draw_text(16, 48, $ep->FONT_24X32, $ep->COLOR_WHITE, $ep->ORIENTATION_HORIZONTAL,
               "Hello World");
$ep->draw();

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
