// This example is not self-contained.
// It requires usage of the example driver specific to your platform.
// See the HAL documentation.

#include "src/bindings/hal_common.h"
#include "src/bindings/bricklet_e_paper_296x128.h"

void check(int rc, const char *msg);
void example_setup(TF_HAL *hal);
void example_loop(TF_HAL *hal);

static TF_EPaper296x128 ep;

void example_setup(TF_HAL *hal) {
	// Create device object
	check(tf_e_paper_296x128_create(&ep, NULL, hal), "create device object");

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

void example_loop(TF_HAL *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
