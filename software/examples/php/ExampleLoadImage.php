<?php

if (!extension_loaded('gd')) {
    echo "Required gd extension is not available\n";
    exit;
}

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletEPaper296x128.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletEPaper296x128;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your E-Paper 296x128 Bricklet
const WIDTH = 296; // Columns
const HEIGHT = 128; // Rows

// Convert GD Image to matching color bool array
function boolArrayFromImage($image, $r, $g, $b)
{
    $pixels = array();

    // Convert image pixels into 8bit pages
    for ($row = 0; $row < HEIGHT; $row++)
    {
        for ($column = 0; $column < WIDTH; $column++)
        {
            $index = imagecolorat($image, $column, $row);
			$color = imagecolorsforindex($image, $index);
	        $pixels[$row*WIDTH + $column] = (($color['red'] == $r) && ($color['green'] == $g) && ($color['blue'] == $b));
        }
    }
    
	return $pixels;
}

$ipcon = new IPConnection(); // Create IP connection
$epaper = new BrickletEPaper296x128(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Download example image here:
// https://raw.githubusercontent.com/Tinkerforge/e-paper-296x128-bricklet/master/software/examples/tf_red.png
$image = imagecreatefrompng('tf_red.png');

// Get black/white pixels from image and write them to the Bricklet buffer
$pixelsBW = boolArrayFromImage($image, 0xFF, 0xFF, 0xFF);
$epaper->writeBlackWhite(0, 0, WIDTH-1, HEIGHT-1, $pixelsBW);

// Get red pixels from image and write them to the Bricklet buffer
$pixelsRed = boolArrayFromImage($image, 0xFF, 0, 0);
$epaper->writeColor(0, 0, WIDTH-1, HEIGHT-1, $pixelsRed);

// Draw buffered values to the display
$epaper->draw();

echo "Press ctrl+c to exit\n";

?>
