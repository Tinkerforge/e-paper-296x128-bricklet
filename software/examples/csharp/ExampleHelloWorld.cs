using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change XYZ to the UID of your E-Paper 296x128 Bricklet

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletEPaper296x128 ep = new BrickletEPaper296x128(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Use black background
		ep.FillDisplay(BrickletEPaper296x128.COLOR_BLACK);

		// Write big white "Hello World" in the middle of the screen
		ep.DrawText(16, 48, BrickletEPaper296x128.FONT_24X32,
		            BrickletEPaper296x128.COLOR_WHITE,
		            BrickletEPaper296x128.ORIENTATION_HORIZONTAL, "Hello World");
		ep.Draw();

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
