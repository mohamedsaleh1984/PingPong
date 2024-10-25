// players vars
float player1_pos = 0.f;
float player1_velocity = 0.f;
float player2_pos = 0.f;
float player2_velocity = 0.f;
const float ACCELERATION_FACTOR = 2000.0f;
const float ACCELERATION_BREAKER_FACTOR = 10.0f;
float arenaHalfSizeX = 85, arenaHalfSizeY = 45;
int player1_score = 0, player2_score = 0;

// collision vars
float playerHalfSizeX = 1.5f;
float playerHalfSizeY = 8;

// ball velocity and acc
float ball_posX = 0.f;
float ball_posY = 0.f;
float ball_velX = 80.f;
float ball_velY = 0.f;
float ballHalfSize = 1.f;
const float ball_velocity_coef = 0.75;


// Key Handling
static bool IsDown(Input* input, enumButtons button) {
	return input->buttons[button].isDown;
}
static bool IsPressed(Input* input, enumButtons button) {
	return input->buttons[button].isDown && input->buttons[button].changed;
}
static bool IsReleased(Input* input, enumButtons button) {
	return !(input->buttons[button].isDown && input->buttons[button].changed);
}

static void simulatePlayer(float* position, float* velocity, float acceleration, float delta) {

	// tweak the speed a little
	acceleration -= (*velocity * ACCELERATION_BREAKER_FACTOR);

	// Calculate New Position = CurrentPosition + V*DeltaT + (A*DeltaT*DeltaT)/2
	*position = *position + (*velocity * delta) + (acceleration * delta * delta) / 2.0f;
	*velocity = *velocity + acceleration * delta;

	// collide to Top Side
	if (*position + playerHalfSizeY > arenaHalfSizeY) {
		//Stop the Player
		*position = arenaHalfSizeY - playerHalfSizeY;

		// Bounce back in different direction
		// velocity *= -1;

		// come to rest
		*velocity = 0;
	} // collide to bottom side
	else if (*position - playerHalfSizeY < -arenaHalfSizeY) {
		*position = -arenaHalfSizeY + playerHalfSizeY;
		*velocity = 0;
	}

}

static void resetBallMoveItToOtherPlayer() {

	if (ball_posX + ballHalfSize > arenaHalfSizeX) {
		ball_velY = 0;
		ball_posX = 0;
		ball_posY = 0;
		ball_velX *= -1;
		player1_score++;
	}

	if (ball_posX + ballHalfSize < -arenaHalfSizeX) {
		ball_velY = 0;
		ball_posX = 0;
		ball_posY = 0;
		ball_velX *= -1;
		player2_score++;
	}
}

static void drawNumber(int number, float x, float y, float size, unsigned int color) {
	float halfSize = size * .5f;
	switch (number) {
	case 0:
		drawRect(x - size, y, halfSize, 2.5f * size, color);
		drawRect(x + size, y, halfSize, 2.5f * size, color);
		drawRect(x, y + size * 2.f, halfSize, halfSize, color);
		drawRect(x, y - size * 2.f, halfSize, halfSize, color);
		break;

	}
}

static void simulateGame(Input* input, float delta) {
	clearScreen(0xff5500);

	// arena
	drawRect(0, 0, arenaHalfSizeX, arenaHalfSizeY, 0xffaa33);

	/******************************************************************************************/
	// Player 1 Settings
	float player1_acceleration = 0.f;
	if (IsDown(input, BUTTON_UP)) {
		player1_acceleration += ACCELERATION_FACTOR;
	}

	if (IsDown(input, BUTTON_DOWN)) {
		player1_acceleration -= ACCELERATION_FACTOR;
	}

	simulatePlayer(&player1_pos, &player1_velocity, player1_acceleration, delta);



	/*******************************************************************************************/
	// Player 2 Settings
	float player2_acceleration = 0.f;
	if (IsDown(input, BUTTON_W)) {
		player2_acceleration += ACCELERATION_FACTOR;
	}

	if (IsDown(input, BUTTON_S)) {
		player2_acceleration -= ACCELERATION_FACTOR;
	}

	simulatePlayer(&player2_pos, &player2_velocity, player2_acceleration, delta);

	/*******************************************************************************************/
	// Ball
	{
		//move towards player 1
		ball_posX += ball_velX * delta;
		ball_posY += ball_velY * delta;

		// Ball Collision on the right Player
		if (ball_posX + ballHalfSize > 80 - playerHalfSizeX &&
			ball_posX - ballHalfSize < 80 + playerHalfSizeX &&
			ball_posY + ballHalfSize > player1_pos - playerHalfSizeY &&
			ball_posY + ballHalfSize < player1_pos + playerHalfSizeY)
		{
			// Change the ball x direction to the opposite side
			ball_posX = 80 - playerHalfSizeX - ballHalfSize;
			ball_velX *= -1;

			// Change Y velocity according to the player velocity
			// ball_velY = player1_velocity * ball_velocity_coef;

			// Make the ball go up or down depends on where ball hit the player
			// Depends on how far the ball center to the player
			// ball_velY = (ball_posY - player1_pos) * ball_velocity_coef;

			// Depends on how far the ball center to the player  AND Player Velocity
			ball_velY = (ball_posY - player1_pos) * ball_velocity_coef + player1_velocity * ball_velocity_coef;
		}

		// Ball Collision on the left Player
		if (ball_posX + ballHalfSize > -80 - playerHalfSizeX &&
			ball_posX - ballHalfSize < -80 + playerHalfSizeX &&
			ball_posY + ballHalfSize > player2_pos - playerHalfSizeY &&
			ball_posY + ballHalfSize < player2_pos + playerHalfSizeY)
		{
			ball_posX = -80 + playerHalfSizeX + ballHalfSize;
			ball_velX *= -1;

			// Depends on how far the ball center to the player  AND Player Velocity
			ball_velY = (ball_posY - player2_pos) * ball_velocity_coef + player2_velocity * ball_velocity_coef;
		}


		// Ball Collision to the Top Wall
		if (ball_posY + ballHalfSize > arenaHalfSizeY) {
			ball_posY = arenaHalfSizeY - ballHalfSize;
			ball_velY *= -1;
		}

		// Ball Collision to the Bottom Wall
		if (ball_posY - ballHalfSize < -arenaHalfSizeY) {
			ball_posY = -arenaHalfSizeY + ballHalfSize;
			ball_velY *= -1;
		}

		// Reset Ball and give it to opposite player
		resetBallMoveItToOtherPlayer();
	}

	// Draw Score
	drawNumber(player1_score, -10, 40, 1.f, 0xbbffbb);
	drawNumber(player2_score, 10, 40, 1.f, 0xbbffbb);

	// Draw the ball
	drawRect(ball_posX, ball_posY, ballHalfSize, ballHalfSize, 0x000000);

	// Right Player
	drawRect(80, player1_pos, playerHalfSizeX, playerHalfSizeY, 0xffC0A0);

	// Left Player
	drawRect(-80, player2_pos, playerHalfSizeX, playerHalfSizeY, 0xff0022);
}