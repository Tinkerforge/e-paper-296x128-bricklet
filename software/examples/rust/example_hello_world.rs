use std::{error::Error, io};

use tinkerforge::{e_paper_296x128_bricklet::*, ip_connection::IpConnection};

const HOST: &str = "localhost";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your E-Paper 296x128 Bricklet.

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection.
    let ep = EPaper296x128Bricklet::new(UID, &ipcon); // Create device object.

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd.
                                          // Don't use device before ipcon is connected.

    // Use black background
    ep.fill_display(E_PAPER_296X128_BRICKLET_COLOR_BLACK).recv()?;

    // Write big white "Hello World" in the middle of the screen
    ep.draw_text(
        16,
        48,
        E_PAPER_296X128_BRICKLET_FONT_24X32,
        E_PAPER_296X128_BRICKLET_COLOR_WHITE,
        E_PAPER_296X128_BRICKLET_ORIENTATION_HORIZONTAL,
        "Hello World".to_string(),
    )
    .recv()?;
    ep.draw().recv()?;

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
