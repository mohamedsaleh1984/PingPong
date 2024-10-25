float player1_pos = 0.f;
float player1_velocity = 0.f;
float player2_pos = 0.f;
float player2_velocity = 0.f;
const float ACCELERATION_FACTOR = 2000.0f;
const float ACCELERATION_BREAKER_FACTOR = 10.0f;
float arenaHalfSizeX = 85, arenaHalfSizeY = 45;

// collision vars
float playerHalfSizeX = 2.5;
float playerHalfSizeY = 12;

// ball velocity and acc
float ball_posX = 0.f;
float ball_posY = 0.f;
float ball_velX = 100.f;
float ball_velY = 0.f;
float ballHalfSize = 1.f;


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

	// tweak the speed a little
	player1_acceleration -= (player1_velocity * ACCELERATION_BREAKER_FACTOR);

	// Calculate New Position = CurrentPosition + V*DeltaT + (A*DeltaT*DeltaT)/2
	player1_pos = player1_pos + (player1_velocity * delta) + (player1_acceleration * delta * delta) / 2.0f;
	player1_velocity = player1_velocity + player1_acceleration * delta;

	// collide to Top Side
	if (player1_pos + playerHalfSizeY > arenaHalfSizeY) {
		//Stop the Player
		player1_pos = arenaHalfSizeY - playerHalfSizeY;

		// Bounce back in different direction
		// player1_velocity *= -1;

		// come to rest
		player1_velocity = 0;
	} // collide to bottom side
	else if (player1_pos - playerHalfSizeY < -arenaHalfSizeY) {
		player1_pos = -arenaHalfSizeY + playerHalfSizeY;
		player1_velocity = 0;
	}


	/*******************************************************************************************/
	// Player 2 Settings
	float player2_acceleration = 0.f;
	if (IsDown(input, BUTTON_W)) {
		player2_acceleration += ACCELERATION_FACTOR;
	}

	if (IsDown(input, BUTTON_S)) {
		player2_acceleration -= ACCELERATION_FACTOR;
	}

	// tweak the speed a little
	player2_acceleration -= (player2_velocity * ACCELERATION_BREAKER_FACTOR);
	player2_pos = player2_pos + (player2_velocity * delta) + (player2_acceleration * delta * delta) / 2.0f;
	player2_velocity = player2_velocity + player2_acceleration * delta;

	// collide to Top Side
	if (player2_pos + playerHalfSizeY > arenaHalfSizeY) {
		//Stop the Player
		player2_pos = arenaHalfSizeY - playerHalfSizeY;

		// Bounce back in different direction
		// player1_velocity *= -1;

		// come to rest
		player2_velocity = 0;
	} // collide to bottom side
	else if (player2_pos - playerHalfSizeY < -arenaHalfSizeY) {
		player2_pos = -arenaHalfSizeY + playerHalfSizeY;
		player2_velocity = 0;
	}


	/*******************************************************************************************/	
	// Ball
	//move towards player 1
	ball_posX += ball_velX * delta;
	ball_posY += ball_velY * delta;

	// Ball Collision on the right Player
	if (ball_posX + ballHalfSize > 80 - playerHalfSizeX && 
		ball_posX - ballHalfSize < 80 + playerHalfSizeX &&
		ball_posY + ballHalfSize > player1_pos - playerHalfSizeY &&
		ball_posY + ballHalfSize < player1_pos + playerHalfSizeY)
	{
		ball_posX = 80 - playerHalfSizeX - ballHalfSize;
		ball_velX *= -1;
	}
	// Ball Collision on the left Player
	if (ball_posX + ballHalfSize > -80 - playerHalfSizeX &&
		ball_posX - ballHalfSize < -80 + playerHalfSizeX &&
		ball_posY + ballHalfSize > player2_pos - playerHalfSizeY &&
		ball_posY + ballHalfSize < player2_pos + playerHalfSizeY)
	{
		ball_posX = -80 + playerHalfSizeX + ballHalfSize;
		ball_velX *= -1;
	}

	// Draw the ball
	drawRect(ball_posX, ball_posY, ballHalfSize, ballHalfSize, 0x000000);


	// Right Player
	drawRect(80, player1_pos, playerHalfSizeX, playerHalfSizeY, 0xffC0A0);
	// Left Player
	drawRect(-80, player2_pos, playerHalfSizeX, playerHalfSizeY, 0xff0022);
}