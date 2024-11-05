#define NOMINMAX
#include <Windows.h>
#include <math.h>
#include <numbers>
#include <chrono>
#include <limits>
#include <string>
#include "player.h"
#include "map.h"

//DEBUG VARS
float testAngle = 0;
float testDist = 0;

const float PI = 3.141592653589793238462643383279502884197169399375105820974944;

const int windowHight = 60; //size of the hight of the window
const int windowWidth = windowHight * 3; //size of the width of the window
const int windowSize = windowHight * windowWidth; //total size of the window. made to be 12:9
const int FOV = 90; //feild of view
const int ViewDistance = 10;

short getWallChar(float distance)
{
	if (distance <= 2.5f)
	{
		return 0x2588;
	}
	else if (distance <= 5)
	{
		return 0x2593;
	}
	else if(distance <= 7.5f)
	{
		return 0x2592;
	}
	else
	{
		return 0x2591;
	}
}

wchar_t getBlankChar(int height)
{
	if (height >= windowHight * 3 / 4)
	{
		if (height <= windowHight * 3 / 4 + ((windowHight - windowHight * 3 / 4) * 1 / 3))
		{
			return '.';
			//return (short)0x00B7;
		}
		else if (height <= windowHight * 3 / 4 + ((windowHight - windowHight * 3 / 4) * 2 / 3))
		{
			return 'o';
			//return (short)0x25CF;
		}
		else
		{
			return'O';
			//return (short)0x25EF;
		}
	}
	else
	{
		return ' ';
	}
}

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
		//Determining FPS
		time1 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = time1 - time2;
		time2 = time1;

		float frameSeconds = (float)elapsedTime.count() / 60;

		//Cast Rays
		for (float i = 0; i < windowWidth; i++) //for each pixel in the width of the screen
		{
			float distance = ViewDistance;
			int blankSurrounds = 0; //The ammount of space characters to leave above and below the wall tile

			float rayAngle = (player1.GetPlayerRot() - FOV / 2) + ((i/windowWidth) * FOV); //make a ray starting at half of the FOV backwards from the player's angle

			float rayAngleRad = (rayAngle < 0 ? rayAngle + 360 : rayAngle) * (PI / 180); //convert ray angle to radians
			float playerRotRad = player1.GetPlayerRot() * (PI / 180);

			/*for (int j = 0; j < ViewDistance; j++) //search for a wall one block at a time
			{
				if (map::CheckWithRay(player1.GetPlayerXPos(), player1.GetPlayerYPos(), rayAngleRad, j)) //if a wall is found by the ray
				{
					distance = j - std::abs((cosf(rayAngleRad) * (player1.GetPlayerYPos() - (int)player1.GetPlayerYPos())) - (sinf(rayAngleRad) * (player1.GetPlayerXPos() - (int)player1.GetPlayerXPos()))); //GIANT statment to say the distance is j - the offset of the player.

					//DEBUG INFO
					if (rayAngle == player1.GetPlayerRot())
					{
						testAngle = rayAngleRad;
						testDist = distance;
					}

					break;
				}
			} for loop replaced with traceback function*/

			distance = map::CheckWithRayAndTraceBack(player1.GetPlayerXPos(), player1.GetPlayerYPos(), rayAngleRad, ViewDistance);
			
			//DEBUG INFO
			if (rayAngle == player1.GetPlayerRot())
			{
				testAngle = rayAngleRad;
				testDist = distance;
			}

			//Write floor to screen
			for (int j = windowHight * 3/4; j < windowHight; j++)
			{
				screen[(int)i + (j * windowWidth)] = (j <= windowHight * 3 / 4 * 1/3 ? (short)0x00B7 : j <= windowHight * 3 / 4 * 2 / 3 ? (short)0x25CF: 'O'); //write each character in the ray's column
			}

			//Write wall to screen
			blankSurrounds = (distance < ViewDistance ? (distance) * (windowHight/20) : windowHight); //ammount of blank spaces above and below wall

			for (int j = 0; j < windowHight; j++)
			{
				screen[(int)i + (j * windowWidth)] = (j < blankSurrounds || windowHight - j < blankSurrounds ? getBlankChar(j) : getWallChar(distance)); //write each character in the ray's column
			}


			//INPUTS

			if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
			{
				player1.SetPlayerRot((player1.GetPlayerRot() < 0 ? 360: player1.GetPlayerRot() - 30.0f * frameSeconds));
			}

			if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
			{
				player1.SetPlayerRot((player1.GetPlayerRot() > 360 ? 0 : player1.GetPlayerRot() + 30.0f * frameSeconds));
			}

			if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
			{
				player1.SetPlayerXPos(player1.GetPlayerXPos() + (sinf(playerRotRad) * frameSeconds));
				player1.SetPlayerYPos(player1.GetPlayerYPos() + (cosf(playerRotRad) * frameSeconds));
			}	

			if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
			{
				player1.SetPlayerXPos(player1.GetPlayerXPos() - (sinf(playerRotRad) * frameSeconds));
				player1.SetPlayerYPos(player1.GetPlayerYPos() - (cosf(playerRotRad) * frameSeconds));
			}
		}

		//DEBUG
		int i = 0;
		float playerRotRad = player1.GetPlayerRot() * (PI / 180);

		for (char ch : std::to_string(player1.GetPlayerXPos()))
		{
			screen[i] = ch;
			i++;
		}

		i++;

		for (char ch : std::to_string(testDist))
		{
			screen[i] = ch;
			i++;
		}

		WriteConsoleOutputCharacter(handle, screen, windowSize, { 0,0 }, &fluff);
	}
}