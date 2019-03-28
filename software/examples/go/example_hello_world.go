package main

import (
	"fmt"
	"github.com/Tinkerforge/go-api-bindings/e_paper_296x128_bricklet"
	"github.com/Tinkerforge/go-api-bindings/ipconnection"
)

const ADDR string = "localhost:4223"
const UID string = "XYZ" // Change XYZ to the UID of your E-Paper 296x128 Bricklet.

func main() {
	ipcon := ipconnection.New()
	defer ipcon.Close()
	ep, _ := e_paper_296x128_bricklet.New(UID, &ipcon) // Create device object.

	ipcon.Connect(ADDR) // Connect to brickd.
	defer ipcon.Disconnect()
	// Don't use device before ipcon is connected.

	// Use black background
	ep.FillDisplay(e_paper_296x128_bricklet.ColorBlack)

	// Write big white "Hello World" in the middle of the screen
	ep.DrawText(16, 48, e_paper_296x128_bricklet.Font24x32,
		e_paper_296x128_bricklet.ColorWhite,
		e_paper_296x128_bricklet.OrientationHorizontal, "Hello World")
	ep.Draw()

	fmt.Print("Press enter to exit.")
	fmt.Scanln()
}
