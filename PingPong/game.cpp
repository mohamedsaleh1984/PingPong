bool IsDown(Input* input, enumButtons button) {
	return input->buttons[button].isDown;
}
bool IsPressed(Input* input, enumButtons button) {
	return input->buttons[button].isDown && input->buttons[button].changed;
}
bool IsReleased(Input* input, enumButtons button) {
	return !(input->buttons[button].isDown && input->buttons[button].changed);
}

float player_pos = 0.f;
float player_velocity = 0.f;

internal void simulateGame(Input* input, float delta) {
	clearScreen(0xff5500);
	// arena
	drawRect(0, 0, 85, 45, 0xffaa33);

	float player_acceleration = 0.f;

	if (IsDown(input, BUTTON_UP)) {
		player_acceleration += 2000;
	}

	if (IsDown(input, BUTTON_DOWN)) {
		player_acceleration -= 2000;
	}

	// tweak the speed a little
	player_acceleration -= (player_velocity * 10.f);

	//New Position = CurrentPosition + V*DeltaT + (A*DeltaT*DeltaT)/2
	player_pos = player_pos + (player_velocity * delta) + (player_acceleration * delta * delta) / 2.0f;
	player_velocity = player_velocity + player_acceleration * delta;


	drawRect(0, 0, 1, 1, 0x000000);
	//Right
	drawRect(80, player_pos, 2.5, 12, 0xffC0A0);
	//Left
	drawRect(-80, 0, 2.5, 12, 0xff0022);
}