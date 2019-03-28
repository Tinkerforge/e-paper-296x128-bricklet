<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletEPaper296x128.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletEPaper296x128;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your E-Paper 296x128 Bricklet

$ipcon = new IPConnection(); // Create IP connection
$ep = new BrickletEPaper296x128(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Use black background
$ep->fillDisplay(BrickletEPaper296x128::COLOR_BLACK);

// Write big white "Hello World" in the middle of the screen
$ep->drawText(16, 48, BrickletEPaper296x128::FONT_24X32,
              BrickletEPaper296x128::COLOR_WHITE,
              BrickletEPaper296x128::ORIENTATION_HORIZONTAL, 'Hello World');
$ep->draw();

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$ipcon->disconnect();

?>
