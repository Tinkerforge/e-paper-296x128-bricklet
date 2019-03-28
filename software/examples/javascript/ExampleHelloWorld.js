var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'XYZ'; // Change XYZ to the UID of your E-Paper 296x128 Bricklet

var ipcon = new Tinkerforge.IPConnection(); // Create IP connection
var ep = new Tinkerforge.BrickletEPaper296x128(UID, ipcon); // Create device object

ipcon.connect(HOST, PORT,
    function (error) {
        console.log('Error: ' + error);
    }
); // Connect to brickd
// Don't use device before ipcon is connected

ipcon.on(Tinkerforge.IPConnection.CALLBACK_CONNECTED,
    function (connectReason) {
        // Use black background
        ep.fillDisplay(Tinkerforge.BrickletEPaper296x128.COLOR_BLACK);

        // Write big white "Hello World" in the middle of the screen
        ep.drawText(16, 48, Tinkerforge.BrickletEPaper296x128.FONT_24X32,
                    Tinkerforge.BrickletEPaper296x128.COLOR_WHITE,
                    Tinkerforge.BrickletEPaper296x128.ORIENTATION_HORIZONTAL,
                    'Hello World');
        ep.draw();
    }
);

console.log('Press key to exit');
process.stdin.on('data',
    function (data) {
        ipcon.disconnect();
        process.exit(0);
    }
);
