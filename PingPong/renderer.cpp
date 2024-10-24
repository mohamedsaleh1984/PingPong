void renderBackground() {
	unsigned int* pixel = (unsigned int*)_renderState.bufferMemory;
	for (int y = 0; y < _renderState.height; ++y) {
		for (int x = 0; x < _renderState.width; ++x) {
			// Change the value of each pixel
			*pixel++ = x * y;
		}
	}
}