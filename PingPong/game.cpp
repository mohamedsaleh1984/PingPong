bool IsDown(Input* input,enumButtons button) {
	return input->buttons[button].isDown;
}
bool IsPressed(Input* input, enumButtons button) {
	return input->buttons[button].isDown && input->buttons[button].changed;
}
bool IsReleased(Input* input, enumButtons button) {
	return !(input->buttons[button].isDown && input->buttons[button].changed);
}

float player_pos = 0.f;

internal void simulateGame(Input* input, float delta) {
	clearScreen(0xff5500);

	// arena
	drawRect(0, 0, 85, 45, 0xffaa33);

	float speed = 50.0f;

	if (IsDown(input,BUTTON_UP)) {
		player_pos += speed * delta;
	}

	if (IsDown(input, BUTTON_DOWN)) {
		player_pos -= speed * delta;
	}


	drawRect(0, 0, 1, 1, 0x000000);
	//Right
	drawRect(80, player_pos, 2.5, 12, 0xffC0A0);
	//Left
	drawRect(-80, 0, 2.5, 12, 0xff0022);
}