#include "utilities.cpp"

internal int clamp(int min, int val, int max) {
	if (val < min)
		return min;

	if (val > max)
		return max;

	return val;
}


internal void
renderBackground() {
	unsigned int* pixel = (unsigned int*)_renderState.bufferMemory;
	for (int y = 0; y < _renderState.height; ++y) {
		for (int x = 0; x < _renderState.width; ++x) {
			// Change the value of each pixel
			*pixel++ = x * y;
		}
	}
}

internal void
clearScreen(unsigned int color) {

	unsigned int* pixel = (unsigned int*)_renderState.bufferMemory;
	for (int y = 0; y < _renderState.height; ++y) {
		for (int x = 0; x < _renderState.width; ++x) {
			// Change the value of each pixel
			*pixel++ = color;
		}
	}
}

internal void
drawRectInPixels(int x0, int y0, int x1, int y1, unsigned int color) {


	// make sure the dimension of drawing within the range of the screen.
	x0 = clamp(0, x0, _renderState.width);
	x1 = clamp(0, x1, _renderState.width);
	y0 = clamp(0, y0, _renderState.height);
	y1 = clamp(0, y1, _renderState.height);

	// Draw the pixels to the memory buffer
	for (int y = y0; y < y1; ++y) {
		unsigned int* pixel = (unsigned int*)_renderState.bufferMemory + x0 + y * _renderState.width;
		for (int x = x0; x < x1; ++x) {
			// Change the value of each pixel
			*pixel++ = color;
		}
	}
}


internal void
drawRect(float x, float y, float halfSizeX, float halfSizeY, unsigned int color) {

	x *= _renderState.height;
	y *= _renderState.height;
	halfSizeX *= _renderState.height;
	halfSizeY *= _renderState.height;

	x += _renderState.width / 2.f;
	y += _renderState.height / 2.f;

	// Change to pixels
	int x0 = x - halfSizeX;
	int x1 = x + halfSizeX;

	int y0 = y - halfSizeY;
	int y1 = y + halfSizeY;

	drawRectInPixels(x0, y0, x1, y1, color);
}

