import java.awt.image.BufferedImage;
import javax.imageio.ImageIO;
import java.io.File;
import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletEPaper296x128;

public class ExampleLoadImage {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;
	private static final String UID = "XZY"; // Change XYZ to the UID of your E-Paper 296x128 Bricklet
	private static final short WIDTH = 296;
	private static final short HEIGHT = 128;

	static boolean[] boolArrayFromImage(BufferedImage image, int color) throws Exception {
		boolean[] pixels = new boolean[HEIGHT * WIDTH];
		short h, w;

		for (h = 0; h < HEIGHT; h++) {
			for (w = 0; w < WIDTH; w++) {
				pixels[h*WIDTH + w] = ((image.getRGB(w, h) & 0x00FFFFFF) == color);
			}
		}

		return pixels;
	}

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletEPaper296x128 epaper = new BrickletEPaper296x128(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Download example image here:
		// https://raw.githubusercontent.com/Tinkerforge/e-paper-296x128-bricklet/master/software/examples/tf_red.png
		BufferedImage image = ImageIO.read(new File("tf_red.png"));

		// Get black/white pixels from image and write them to the Bricklet buffer
		boolean[] pixelsBW = boolArrayFromImage(image, 0xFFFFFF);
		epaper.writeBlackWhite(0, 0, WIDTH-1, HEIGHT-1, pixelsBW);

		// Get red pixels from image and write them to the Bricklet buffer
		boolean[] pixelsRed = boolArrayFromImage(image, 0xFF0000);
		epaper.writeColor(0, 0, WIDTH-1, HEIGHT-1, pixelsRed);

		// Draw buffered values to the display
		epaper.draw();
	}
}
