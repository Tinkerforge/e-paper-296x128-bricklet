#!/usr/bin/perl

use strict;
use Math::Trig;
use Term::ReadKey;
use GD;
use Tinkerforge::IPConnection;
use Tinkerforge::BrickletEPaper296x128;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change XYZ to the UID of your E-Paper 296x128 Bricklet
use constant WIDTH => 296;
use constant HEIGHT => 128;

# Convert GD Image to matching color bool array
sub bool_array_from_image
{
    my ($image, $cmp_r, $cmp_g, $cmp_b) = @_;
    my @pixels = ();

    foreach my $row (0..&HEIGHT - 1) {
        foreach my $column (0..&WIDTH - 1) {
            (my $r, my $g, my $b) = $image->rgb($image->getPixel($column, $row));
            $pixels[$row*&WIDTH + $column] = (($r == $cmp_r) && ($g == $cmp_g) && ($b == $cmp_b));
        }
    }

	 return @pixels;
}

GD::Image->trueColor(1);

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $epaper = Tinkerforge::BrickletEPaper296x128->new(&UID, $ipcon); # Create device object
$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Download example image here:
# https://raw.githubusercontent.com/Tinkerforge/e-paper-296x128-bricklet/master/software/examples/tf_red.png
my $image = newFromPng GD::Image('tf_red.png');

# Get black/white pixels from image and write them to the Bricklet buffer
my @pixels_bw = bool_array_from_image($image, 0xFF, 0xFF, 0xFF);
$epaper->write_black_white(0, 0, &WIDTH-1, &HEIGHT-1, \@pixels_bw);

# Get red pixels from image and write them to the Bricklet buffer
my @pixels_red = bool_array_from_image($image, 0xFF, 0, 0);
$epaper->write_color(0, 0, &WIDTH-1, &HEIGHT-1, \@pixels_red);

# Draw buffered values to the display
$epaper->draw();

print "Press key to exit\n";
ReadMode(0);
$ipcon->disconnect();
