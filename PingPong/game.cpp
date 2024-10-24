bool IsDown(Input* input,enumButtons button) {
	return input->buttons[button].isDown;
}
bool IsPressed(Input* input, enumButtons button) {
	return input->buttons[button].isDown && input->buttons[button].changed;
}
bool IsReleased(Input* input, enumButtons button) {
	return !(input->buttons[button].isDown && input->buttons[button].changed);
}

float player_pos_x = 0.f;
float player_pos_y = 0.f;
float speed = 0.2f;


internal void simulateGame(Input* input) {
	clearScreen(0xff5500);

	if (IsDown(input,BUTTON_UP)) {
		player_pos_y += speed;
	}

	if (IsDown(input, BUTTON_DOWN)) {
		player_pos_y -= speed;
	}

	if (IsDown(input, BUTTON_LEFT)) {
		player_pos_x -= speed;
	}

	if (IsDown(input, BUTTON_RIGHT)) {
		player_pos_x += speed;
	}

	drawRect(player_pos_x, player_pos_y, 1, 1, 0xff0000);
	drawRect(30, 40, 5, 5, 0xffC0A0);
	drawRect(-20, 20, 8, 8, 0xff0022);/**/
}