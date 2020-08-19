

#include "bindings/hal_common.h"
#include "bindings/bricklet_e_paper_296x128.h"

#define UID "XYZ" // Change XYZ to the UID of your E-Paper 296x128 Bricklet

void check(int rc, const char* msg);




TF_EPaper296x128 ep;

void example_setup(TF_HalContext *hal) {
	// Create device object
	check(tf_e_paper_296x128_create(&ep, UID, hal), "create device object");


	// Use black background
	check(tf_e_paper_296x128_fill_display(&ep,
	                                      TF_E_PAPER_296X128_COLOR_BLACK), "call fill_display");

	// Write big white "Hello World" in the middle of the screen
	check(tf_e_paper_296x128_draw_text(&ep, 16, 48, TF_E_PAPER_296X128_FONT_24X32,
	                                   TF_E_PAPER_296X128_COLOR_WHITE,
	                                   TF_E_PAPER_296X128_ORIENTATION_HORIZONTAL,
	                                   "Hello World"), "call draw_text");
	check(tf_e_paper_296x128_draw(&ep), "call draw");

}

void example_loop(TF_HalContext *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
