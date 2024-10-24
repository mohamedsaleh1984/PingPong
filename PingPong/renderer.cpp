#include "utilities.cpp"

void renderBackground() {
	unsigned int* pixel = (unsigned int*)_renderState.bufferMemory;
	for (int y = 0; y < _renderState.height; ++y) {
		for (int x = 0; x < _renderState.width; ++x) {
			// Change the value of each pixel
			*pixel++ = x * y;
		}
	}
}

void clearScreen(unsigned int color) {

	unsigned int* pixel = (unsigned int*)_renderState.bufferMemory;
	for (int y = 0; y < _renderState.height; ++y) {
		for (int x = 0; x < _renderState.width; ++x) {
			// Change the value of each pixel
			*pixel++ = color;
		}
	}
}


void drawRect(int x0, int y0, int x1, int y1, unsigned int color) {

	//make sure the dimension of drawing within the range of the screen.
	x0 = clamp(0, x0, _renderState.width);
	x1 = clamp(0, x1, _renderState.width);
	y0 = clamp(0, y0, _renderState.height);
	y1 = clamp(0, y1, _renderState.height);


	for (int y = y0; y < y1; ++y) {
		unsigned int* pixel = (unsigned int*)_renderState.bufferMemory + x0 + y * _renderState.width;
		for (int x = x0; x < x1; ++x) {
			// Change the value of each pixel
			*pixel++ = color;
		}
	}
}