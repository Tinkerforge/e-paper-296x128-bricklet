extern crate image; // Add 'image = "0.20"' to dependencies in Cargo.toml

use std::{error::Error, io};
use std::path::Path;
use image::RgbImage;

use tinkerforge::{e_paper_296x128_bricklet::*, ip_connection::IpConnection};

const HOST: &str = "localhost";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your E-Paper 296x128 Bricklet.

const WIDTH: u32 = 296;
const HEIGHT: u32 = 128;

// Convert RgbImage to matching color bool array
fn bool_array_from_image(image: &RgbImage, r: u8, g: u8, b: u8) -> Vec<bool> {
	let mut pixels = vec![false; (WIDTH * HEIGHT) as usize];
	for row in 0..HEIGHT-1 {
		for column in 0..WIDTH-1 {
			let pixel = image.get_pixel(column, row);
			pixels[(row * WIDTH + column) as usize] = (pixel[0] == r) && (pixel[1] == g) && (pixel[2] == b);
		}
	}

	pixels
}

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection.
    let ep = EPaper296x128Bricklet::new(UID, &ipcon); // Create device object.

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd.
                                          // Don't use device before ipcon is connected.

	// Download example image here:
	// https://raw.githubusercontent.com/Tinkerforge/e-paper-296x128-bricklet/master/software/examples/tf_red.png
	let image = image::open(&Path::new("tf_red.png")).unwrap().to_rgb();

	// Get black/white pixels from image and write them to the Bricklet buffer
	let pixels_bw = bool_array_from_image(&image, 0xFF, 0xFF, 0xFF);
	let _  =ep.write_black_white(0, 0, (WIDTH-1) as u16, (HEIGHT-1) as u8, &pixels_bw);

	// Get red pixels from image and write them to the Bricklet buffer
	let pixels_red = bool_array_from_image(&image, 0xFF, 0, 0);
	let _ = ep.write_color(0, 0, (WIDTH-1) as u16, (HEIGHT-1) as u8, &pixels_red);

	// Draw buffered values to the display
	ep.draw();

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
