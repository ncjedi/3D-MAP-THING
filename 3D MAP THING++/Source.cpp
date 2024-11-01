#define NOMINMAX
#include <Windows.h>
#include <math.h>
#include <numbers>
#include <chrono>
#include <limits>
#include "player.h"
#include "map.h"

const float PI = 3.141592653589793238462643383279502884197169399375105820974944;

const int windowHight = 60; //size of the hight of the window
const int windowWidth = windowHight * 2; //size of the width of the window
const int windowSize = windowHight * windowWidth; //total size of the window. made to be 12:9
const int FOV = 90; //feild of view
const int ViewDistance = 4;

int main()
{
	//Windows Console Configuration @_@
	wchar_t screen[windowSize]; //array of characters to print to the screen
	screen[windowSize - 1] = '\0'; //character to represent the end of the string

	HANDLE handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); //Creates a new console handle so i can mess with console configurations. the console created is nothing special just what i'm going to do TO IT
	SetConsoleActiveScreenBuffer(handle); //Sets the new handle to be the active console
	
	CONSOLE_CURSOR_INFO* cursor = new CONSOLE_CURSOR_INFO{ 1, false }; //makes the cursor INVISIBLE
	SetConsoleCursorInfo(handle, cursor); //sets the invisible cursor to be the active cursor

	DWORD fluff = 0; //used for the output but no one knows why
	//Console Configuration END ^_^

	player player1 = player();
	map::buildMap();

	auto time1 = std::chrono::system_clock::now();
	auto time2 = std::chrono::system_clock::now();

	while (true)
	{
		time1 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = time1 - time2;
		time2 = time1;

		for (float i = 0; i < windowWidth; i++) //for each pixel in the width of the screen
		{
			float distance = 4.0f;
			int blankSurrounds = 0; //The ammount of space characters to leave above and below the wall tile

			float rayAngle = (player1.GetPlayerRot() - FOV / 2) + ((i/windowWidth) * FOV); //make a ray starting at half of the FOV backwards from the player's angle

			float rayAngleRad = (rayAngle < 0 ? rayAngle + 360 : rayAngle) * (PI / 180); //convert ray angle to radians

			for (int j = 0; j < ViewDistance; j++) //search for a wall one block at a time
			{
				if (map::CheckWithRay(player1.GetPlayerXPos(), player1.GetPlayerYPos(), rayAngleRad, j)) //if a wall is found by the ray
				{
					distance = j - ((rayAngle < 135 && rayAngle > 45) || (rayAngle < 315 && rayAngle > 225) ? (player1.GetPlayerYPos() - (int)player1.GetPlayerYPos()) : (player1.GetPlayerXPos() - (int)player1.GetPlayerXPos())); //GIANT statment to say the distance is j - the offset of the player. if the angle is between 45 and 135 or 225 and 315 then use the Y offset. otherwise use the X offset
					break;
				}
			}

			blankSurrounds = (distance < 4.0f ? distance * (windowHight/20) : windowHight);

			for (int j = 0; j < windowHight; j++)
			{
				screen[(int)i + (j * windowWidth)] = (j < blankSurrounds || windowHight - j < blankSurrounds ? ' ' : '#');
			}

			if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
			{
				player1.SetPlayerRot((player1.GetPlayerRot() < 0 ? 355: player1.GetPlayerRot() - 0.5f * (float)elapsedTime.count()));
			}
		}

		WriteConsoleOutputCharacter(handle, screen, windowSize, { 0,0 }, &fluff);
	}
}