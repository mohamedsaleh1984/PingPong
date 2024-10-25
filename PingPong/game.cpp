#include "utilities.cpp"
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
float ball_velX = 150.f;
float ball_velY = 0.f;
float ballHalfSize = 1.f;
const float ball_velocity_coef = 0.75;

// letters and numbers
const char* letters[][7] = {
	" 00",
	"0  0",
	"0  0",
	"0000",
	"0  0",
	"0  0",
	"0  0",

	"000",
	"0  0",
	"0  0",
	"000",
	"0  0",
	"0  0",
	"000",

	" 000",
	"0",
	"0",
	"0",
	"0",
	"0",
	" 000",

	"000",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"000",

	"0000",
	"0",
	"0",
	"000",
	"0",
	"0",
	"0000",

	"0000",
	"0",
	"0",
	"000",
	"0",
	"0",
	"0",

	" 000",
	"0",
	"0",
	"0 00",
	"0  0",
	"0  0",
	" 000",

	"0  0",
	"0  0",
	"0  0",
	"0000",
	"0  0",
	"0  0",
	"0  0",

	"000",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",
	"000",

	" 000",
	"   0",
	"   0",
	"   0",
	"0  0",
	"0  0",
	" 000",

	"0  0",
	"0  0",
	"0 0",
	"00",
	"0 0",
	"0  0",
	"0  0",

	"0",
	"0",
	"0",
	"0",
	"0",
	"0",
	"0000",

	"00 00",
	"0 0 0",
	"0 0 0",
	"0   0",
	"0   0",
	"0   0",
	"0   0",

	"00  0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0  00",

	"0000",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0000",

	" 000",
	"0  0",
	"0  0",
	"000",
	"0",
	"0",
	"0",

	" 000 ",
	"0   0",
	"0   0",
	"0   0",
	"0 0 0",
	"0  0 ",
	" 00 0",

	"000",
	"0  0",
	"0  0",
	"000",
	"0  0",
	"0  0",
	"0  0",

	" 000",
	"0",
	"0 ",
	" 00",
	"   0",
	"   0",
	"000 ",

	"000",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",

	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	" 00",

	"0   0",
	"0   0",
	"0   0",
	"0   0",
	"0   0",
	" 0 0",
	"  0",

	"0   0 ",
	"0   0",
	"0   0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	" 0 0 ",

	"0   0",
	"0   0",
	" 0 0",
	"  0",
	" 0 0",
	"0   0",
	"0   0",

	"0   0",
	"0   0",
	" 0 0",
	"  0",
	"  0",
	"  0",
	"  0",

	"0000",
	"   0",
	"  0",
	" 0",
	"0",
	"0",
	"0000",

	"",
	"",
	"",
	"",
	"",
	"",
	"0",

	"   0",
	"  0",
	"  0",
	" 0",
	" 0",
	"0",
	"0",
};
static void drawNumber(int number, float x, float y, float size, unsigned int color);
static void drawText(const char* text, float x, float y, float size, unsigned int color);
//***************************************************************************************

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

static void aiStrategy1(float* player1_acceleration) {
	if (ball_posY > player1_pos + 2.f)*player1_acceleration += 1300;
	if (ball_posY < player1_pos - 2.f)*player1_acceleration -= 1300;
}

static void aiStrategy2(float* player1_acceleration) {
	*player1_acceleration = (ball_posY - player1_pos) * 100;
	if (*player1_acceleration > 1300)*player1_acceleration = 1300;
	if (*player1_acceleration < -1300)*player1_acceleration = -1300;
}

// Game Mode
enum GameMode {
	GM_MENU,
	GM_GAMEPLAY
};

GameMode currentGameMode = GM_MENU;
bool selectedButton = false;
bool isAiEnemy = selectedButton;

static void simulateGame(Input* input, float delta) {
	clearScreen(0xff5500);

	// arena
	drawRect(0, 0, arenaHalfSizeX, arenaHalfSizeY, 0xffaa33);

	if (currentGameMode == GM_GAMEPLAY) {
		/******************************************************************************************/
		// Player 1 Settings
		float player1_acceleration = 0.f;
		if (!isAiEnemy) {
			if (IsDown(input, BUTTON_UP)) player1_acceleration += ACCELERATION_FACTOR;
			if (IsDown(input, BUTTON_DOWN))  player1_acceleration -= ACCELERATION_FACTOR;
		}
		else {
			//AI Agent
			aiStrategy2(&player1_acceleration);
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

	if (currentGameMode == GM_MENU) {

		drawText("AI", 0, 0, 1, 0x145264);

		if (IsPressed(input, BUTTON_LEFT) || IsPressed(input, BUTTON_RIGHT)) {
			selectedButton = !selectedButton;
		}

		if (IsPressed(input, BUTTON_ENTER)) {
			currentGameMode = GM_GAMEPLAY;
		}

		if (!selectedButton) {
			drawRect(10, 10, 5, 5, 0xFF0000);
			drawRect(-10, 10, 5, 5, 0xAAccDD);
		}
		else {
			drawRect(10, 10, 5, 5, 0xAAccDD);
			drawRect(-10, 10, 5, 5, 0xFF0000);
		}
	}
}

static void drawNumber(int number, float x, float y, float size, unsigned int color) {
	float halfSize = size * .5f;
	bool drew_number = false;
	while (number || !drew_number) {
		drew_number = true;

		int digit = number % 10;
		number = number / 10;

		switch (digit) {
		case 0: {
			drawRect(x - size, y, halfSize, 2.5f * size, color);
			drawRect(x + size, y, halfSize, 2.5f * size, color);
			drawRect(x, y + size * 2.f, halfSize, halfSize, color);
			drawRect(x, y - size * 2.f, halfSize, halfSize, color);
			x -= size * 4.f;
		} break;

		case 1: {
			drawRect(x + size, y, halfSize, 2.5f * size, color);
			x -= size * 2.f;
		} break;

		case 2: {
			drawRect(x, y + size * 2.f, 1.5f * size, halfSize, color);
			drawRect(x, y, 1.5f * size, halfSize, color);
			drawRect(x, y - size * 2.f, 1.5f * size, halfSize, color);
			drawRect(x + size, y + size, halfSize, halfSize, color);
			drawRect(x - size, y - size, halfSize, halfSize, color);
			x -= size * 4.f;
		} break;

		case 3: {
			drawRect(x - halfSize, y + size * 2.f, size, halfSize, color);
			drawRect(x - halfSize, y, size, halfSize, color);
			drawRect(x - halfSize, y - size * 2.f, size, halfSize, color);
			drawRect(x + size, y, halfSize, 2.5f * size, color);
			x -= size * 4.f;
		} break;

		case 4: {
			drawRect(x + size, y, halfSize, 2.5f * size, color);
			drawRect(x - size, y + size, halfSize, 1.5f * size, color);
			drawRect(x, y, halfSize, halfSize, color);
			x -= size * 4.f;
		} break;

		case 5: {
			drawRect(x, y + size * 2.f, 1.5f * size, halfSize, color);
			drawRect(x, y, 1.5f * size, halfSize, color);
			drawRect(x, y - size * 2.f, 1.5f * size, halfSize, color);
			drawRect(x - size, y + size, halfSize, halfSize, color);
			drawRect(x + size, y - size, halfSize, halfSize, color);
			x -= size * 4.f;
		} break;

		case 6: {
			drawRect(x + halfSize, y + size * 2.f, size, halfSize, color);
			drawRect(x + halfSize, y, size, halfSize, color);
			drawRect(x + halfSize, y - size * 2.f, size, halfSize, color);
			drawRect(x - size, y, halfSize, 2.5f * size, color);
			drawRect(x + size, y - size, halfSize, halfSize, color);
			x -= size * 4.f;
		} break;

		case 7: {
			drawRect(x + size, y, halfSize, 2.5f * size, color);
			drawRect(x - halfSize, y + size * 2.f, size, halfSize, color);
			x -= size * 4.f;
		} break;

		case 8: {
			drawRect(x - size, y, halfSize, 2.5f * size, color);
			drawRect(x + size, y, halfSize, 2.5f * size, color);
			drawRect(x, y + size * 2.f, halfSize, halfSize, color);
			drawRect(x, y - size * 2.f, halfSize, halfSize, color);
			drawRect(x, y, halfSize, halfSize, color);
			x -= size * 4.f;
		} break;

		case 9: {
			drawRect(x - halfSize, y + size * 2.f, size, halfSize, color);
			drawRect(x - halfSize, y, size, halfSize, color);
			drawRect(x - halfSize, y - size * 2.f, size, halfSize, color);
			drawRect(x + size, y, halfSize, 2.5f * size, color);
			drawRect(x - size, y + size, halfSize, halfSize, color);
			x -= size * 4.f;
		} break;
		}

	}

}

static void drawText(const char* text, float x, float y, float size, unsigned int color) {

	float halfSize = size * .5f;
	float originalY = y;

	while (*text) {
		// not space character
		if (*text != 32) {
			const char** letter = letters[*text - 'A'];
			float originalX = x;
			for (int i = 0; i < 7; i++) {
				const char* row = letter[i];
				while (*row) {
					if (*row == '0') {
						drawRect(x, y, halfSize, halfSize, color);
					}
					x += size;
					row++;
				}
				y -= size;
				x = originalX;
			}
		}

		//move to next letter
		text++;
		// move to next x-axis 
		x += size * 6.f;
		// move to original y position.
		y = originalY;
	}
}