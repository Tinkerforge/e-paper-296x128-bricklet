function octave_example_hello_world()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your E-Paper 296x128 Bricklet

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    ep = javaObject("com.tinkerforge.BrickletEPaper296x128", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Use black background
    ep.fillDisplay(ep.COLOR_BLACK);

    % Write big white "Hello World" in the middle of the screen
    ep.drawText(16, 48, ep.FONT_24X32, ep.COLOR_WHITE, ep.ORIENTATION_HORIZONTAL, ...
                "Hello World");
    ep.draw();

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end
