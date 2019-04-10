using System;
using System.Drawing;
using System.Threading;
using Tinkerforge;

// Tested with 
// > mcs /reference:System.Drawing.dll /target:exe /out:Example.exe /reference:Tinkerforge.dll ExampleLoadImage.cs

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change XYZ to the UID of your E-Paper 296x128 Bricklet
	private static int WIDTH = 296;
	private static int HEIGHT = 128;

	// Convert C# Bitmap to matching color bool array
	private static bool[] BoolArrayFromImage(Bitmap bitmap, Color color)
	{ 
		bool[] pixels = new bool[HEIGHT*WIDTH];

		for (int row = 0; row < HEIGHT; row++)
		{
			for (int column = 0; column < WIDTH; column++)
			{
				Color c = bitmap.GetPixel(column, row);
				pixels[row*WIDTH + column] = ((c.R == color.R) && (c.G == color.G) && (c.B == color.B));
			}
		}

		return pixels;
	}

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletEPaper296x128 epaper = new BrickletEPaper296x128(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Download example image here:
		// https://raw.githubusercontent.com/Tinkerforge/e-paper-296x128-bricklet/master/software/examples/tf_red.png
		Bitmap bitmap = new Bitmap("tf_red.png");

		// Get black/white pixels from image and write them to the Bricklet buffer
		bool[] pixelsBW = BoolArrayFromImage(bitmap, Color.White);
		epaper.WriteBlackWhite(0, (byte)0, WIDTH-1, (byte)(HEIGHT-1), pixelsBW);

		// Get red pixels from image and write them to the Bricklet buffer
		bool[] pixelsRed = BoolArrayFromImage(bitmap, Color.Red);
		epaper.WriteColor(0, (byte)0, WIDTH-1, (byte)(HEIGHT-1), pixelsRed);

		// Draw buffered values to the display
		epaper.Draw();

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
