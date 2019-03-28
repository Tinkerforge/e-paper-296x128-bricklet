import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletEPaper296x128;

public class ExampleHelloWorld {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;

	// Change XYZ to the UID of your E-Paper 296x128 Bricklet
	private static final String UID = "XYZ";

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletEPaper296x128 ep = new BrickletEPaper296x128(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Use black background
		ep.fillDisplay(BrickletEPaper296x128.COLOR_BLACK);

		// Write big white "Hello World" in the middle of the screen
		ep.drawText(16, 48, BrickletEPaper296x128.FONT_24X32,
		            BrickletEPaper296x128.COLOR_WHITE,
		            BrickletEPaper296x128.ORIENTATION_HORIZONTAL, "Hello World");
		ep.draw();

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
