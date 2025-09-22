#include "raylib.h"
#include "string"
#include "iostream"

using namespace std;

/*
README-------------------------------------
Team roles: Noah: Lead programmer, basic game mechanics, basic game design,
Simon: Main programmer, advanced game mechanics, advanced game design,
Alvin: Help with programming, scoreboards, file handling, Calculations
Oskar: Lead designer, graphics, 2D art, Audio design
(Note, any team member can help with any task, but these are the main roles)

To do list Noah: 23/09
I FIXED IT! After 2 hours of trial and error with github ignored, I fixed the github issue!
Holy shit!
Add Start menu, game over screen and setup basic main screen (simple shapes to start)
Add basic collisons system using raylib collison check

Add basic scoring system using raylib text display

Add basic player system:
Rectangle that can increase height, and rotate based on fall speed
Add basic gravity system, where player falls when not pressing space or mouseclick

Add basic object system:
Add basic spawn and despawn system for hindrance objects
rectangles that move left across the screen, despawn when off screen
random height of base, identical height increase (gap) between top and bottom
top and bottom rectangles are tall enough so player cannot go "above"
Fixed width of rectangles

Controls:
Space or mouseclick to increase height of player

Scene list-----------------------------------------------------------------------
Start menu:
Space or mouseclick anywhere to start
High score display center screen

Main game:
Player moves only Y axis
Player rotates slightly when moving up or down
Gravity pulls player down when not pressing space or mouseclick

Objects move only X axis
Objects spawn on right side of screen and despawn on left side of screen
objects spawn at random heights but fixed distance between top and bottom and fixed width
objects spawn are tall enough to leave a gap for the player to pass through
objects spawned are tall enough so player cannot go "above"

Touching the "ground" or "floor" ends the game
Touching an object ends the game
Score increases by 1 for each object that passes the player

Background: Solid color background (light blue?)
Clouds that move slowly across the screen to indicate speed(parallax effect)
Perhaps ground or floor at the bottom of the screen moves slightly to indicate speed(parallax effect)

Game over screen with score and high score:
Space or mouseclick anywhere to restart

Scene list end-------------------------------------------------------------------

TO DO LATER (if time):

Add features: Noah and Simon tasks:
Powerups? Different object types? Different player types? Changing background?
Add more menus: Pause menu? Settings menu?

Graphics (textures onto rectangles): Oskar tasks
Add more advanced graphics: animated player? animated objects? animated background?
Music: (Background music, menu music)
Sound effects: game over(wumpwump), score increase (Ding), height increase sound (Swosh)

Scoreboards: Alvin Tasks
Add basic high score system using raylib text display and file handling
Figure out math for paralaxing and centering of text and data

END README------------------------------
---------------------------------------------
*/

//----------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

//Global variables
typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, GAMEOVER } GameScreen;

//Load textures here
Texture2D backgroundLogoScreen = LoadTexture("resources/logo_background.png");

//helper functions
void DrawCenteredText(const char* text, int posY, int fontSize, Color color)
{
	// Measure the width of the text
	float textWidth = MeasureText(text, fontSize);

	// Calculate the X position to center the text
	// GetScreenWidth() is a Raylib function that returns the current screen width
	float posX = (GetScreenWidth() / 2.0f) - (textWidth / 2.0f);

	// Draw the text at the calculated position
	DrawText(text, (int)posX, posY, fontSize, color);
}

int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 1200;
	const int screenHeight = 800;

	GameScreen currentScreen = LOGO;

	int gameActive = 0;

	int framesCounter = 0;

	InitWindow(screenWidth, screenHeight, "FlappyPlane, Space or mouseclick to start");

	Vector2 ballPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };

	SetTargetFPS(120);

	//--------------------------------------------------------------------------------------
	// Main game loop
	while (!WindowShouldClose())
	{
		switch (currentScreen)
		{
		case LOGO:
		{
			// TODO: Update LOGO screen variables here!
			gameActive = 2; // set gameActive to 2 when showing logo
			framesCounter++;

			// Wait for 3 seconds (360/120 frames per second) before jumping to TITLE screen
			if (framesCounter > 360)
			{
				currentScreen = TITLE;
			}
		} break;
		case TITLE:
		{
			// TODO: Update TITLE screen variables here!

			// Press enter to change to GAMEPLAY screen
			if (IsKeyPressed(KEY_SPACE) || IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			{
				currentScreen = GAMEPLAY;
				gameActive = 1; // set gameActive to 1 when starting the game
			}
		} break;
		case GAMEPLAY:
		{
			// TODO: Update GAMEPLAY screen variables here!
			  // Update
		//----------------------------------------------------------------------------------
			if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 2.0f;
			if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 2.0f;
			if (IsKeyDown(KEY_UP)) ballPosition.y -= 2.0f;
			if (IsKeyDown(KEY_DOWN)) ballPosition.y += 2.0f;

			if (ballPosition.x < 0 || ballPosition.x > screenWidth || ballPosition.y < 0 || ballPosition.y > screenHeight)
			{
				gameActive = 4; // set gameActive to 4 if the ball goes out of bounds
				// reset ball position to center
				ballPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };
			}

			// go out of bounds to end game
			if (gameActive == 4)
			{
				currentScreen = GAMEOVER;
			}
		} break;
		case GAMEOVER:
		{
			// TODO: Update ENDING screen variables here!

			// Press Spacebar or mouseleft to return to TITLE screen
			if (IsKeyPressed(KEY_SPACE) || IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			{
				gameActive = 0; // reset gameActive
				currentScreen = GAMEPLAY;
			}
		} break;
		default: break;
		}

		//----------------------------------------------------------------------------------
		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		switch (currentScreen)
		{
		case LOGO:
		{
			// TODO: Draw LOGO screen here!
			DrawTexture(backgroundLogoScreen, 0, 0, WHITE);
			DrawCenteredText("LOGO SCREEN", (float)screenHeight / 2, 50, LIGHTGRAY);
			DrawCenteredText("WAIT for 3 SECONDS...", (float)screenHeight / 2 - 100, 40, GRAY);
		} break;
		case TITLE:
		{
			// TODO: Draw TITLE screen here!
			DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
			DrawCenteredText("FLAPPY PLAAAAANE", (float)screenHeight / 2 - 100, 50, DARKGREEN);
			DrawCenteredText("PRESS SPACE/Left Click to Play", (float)screenHeight / 2 - 200, 40, DARKGREEN);
		} break;
		case GAMEPLAY:
		{
			// TODO: Draw GAMEPLAY screen here!
			DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);

			DrawCenteredText("move the ball with arrow keys", (float)screenHeight / 2 - 100, 40, DARKGRAY);

			DrawCircleV(ballPosition, 50, BLUE);

			DrawCenteredText("GAMEPLAY SCREEN", (float)screenHeight / 2 - 200, 40, MAROON);
		} break;
		case GAMEOVER:
		{
			// TODO: Draw GAMEOVER screen here!
			DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
			DrawCenteredText("Game Over", (float)screenHeight / 2 - 100, 50, DARKBLUE);
			DrawCenteredText("GAME OVER! PRESS SPACE or Left Click to TRY AGAIN!", (float)screenHeight / 2, 40, DARKBLUE);
		} break;
		default: break;
		}

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	UnloadTexture(backgroundLogoScreen);
	CloseWindow();      
	//--------------------------------------------------------------------------------------

	return 0;
}