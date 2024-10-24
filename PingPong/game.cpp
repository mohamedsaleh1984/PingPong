
internal void simulateGame(Input* input) {
	clearScreen(0xff5500);

	if (input->buttons[BUTTON_UP].isDown) {
		drawRect(0, 0, 1, 1, 0xff0000);
	}

	drawRect(30, 40, 5, 5, 0xffC0A0);
	drawRect(-20, 20, 8, 8, 0xff0022);/**/
}