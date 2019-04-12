package main

import (
	"fmt"
	"os"
	"image"
	"image/png"
	"github.com/Tinkerforge/go-api-bindings/e_paper_296x128_bricklet"
	"github.com/Tinkerforge/go-api-bindings/ipconnection"
)

const ADDR string = "localhost:4223"
const UID string = "XYZ" // Change XYZ to the UID of your E-Paper 296x128 Bricklet.
const WIDTH = 296
const HEIGHT = 128

// Convert Image to matching color bool array
func BoolArrayFromImage(image image.Image, r uint32, g uint32, b uint32) ([]bool, error) {
	var pixels []bool
	for row := 0; row < HEIGHT; row++ {
		for column := 0; column < WIDTH; column++ {
			rCmp, gCmp, bCmp, _ := image.At(column, row).RGBA();
			pixels = append(pixels, (rCmp == r) && (gCmp == g) && (bCmp == b))
		}
	}

	return pixels, nil
}

func main() {
	ipcon := ipconnection.New()
	defer ipcon.Close()
	ep, _ := e_paper_296x128_bricklet.New(UID, &ipcon) // Create device object.

	ipcon.Connect(ADDR) // Connect to brickd.
	defer ipcon.Disconnect()
	// Don't use device before ipcon is connected.

	// Download example image here:
	// https://raw.githubusercontent.com/Tinkerforge/e-paper-296x128-bricklet/master/software/examples/tf_red.png
	image.RegisterFormat("png", "png", png.Decode, png.DecodeConfig)
	file, _ := os.Open("tf_red.png")
	defer file.Close()
	image, _, _ := image.Decode(file)

	// Get black/white pixels from image and write them to the Bricklet buffer
	pixelsBW, _ := BoolArrayFromImage(image, 0xFFFF, 0xFFFF, 0xFFFF)
	ep.WriteBlackWhite(0, 0, WIDTH-1, HEIGHT-1, pixelsBW)

	// Get red pixels from image and write them to the Bricklet buffer
	pixelsRed, _ := BoolArrayFromImage(image, 0xFFFF, 0, 0)
	ep.WriteColor(0, 0, WIDTH-1, HEIGHT-1, pixelsRed)

	// Draw buffered values to the display
	ep.Draw()

	fmt.Print("Press enter to exit.")
	fmt.Scanln()
}
