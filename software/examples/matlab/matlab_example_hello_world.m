function matlab_example_hello_world()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletEPaper296x128;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change XYZ to the UID of your E-Paper 296x128 Bricklet

    ipcon = IPConnection(); % Create IP connection
    ep = handle(BrickletEPaper296x128(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Use black background
    ep.fillDisplay(BrickletEPaper296x128.COLOR_BLACK);

    % Write big white "Hello World" in the middle of the screen
    ep.drawText(16, 48, BrickletEPaper296x128.FONT_24X32, ...
                BrickletEPaper296x128.COLOR_WHITE, ...
                BrickletEPaper296x128.ORIENTATION_HORIZONTAL, 'Hello World');
    ep.draw();

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end
