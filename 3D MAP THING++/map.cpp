#include "map.h"

wchar_t map::mapArray[size * size] = {};

void map::buildMap()
{
	wchar_t tempArray[size * size] = {
		'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
		'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
		'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
		'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
		'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
		'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
		'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
		'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
		'#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
		'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
		'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
		'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#',
		'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
		'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
		'#',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
		'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
		'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
		'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
		'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
		'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'
	};

	for (int i = 0; i < size * size; i++)
	{
		mapArray[i] = tempArray[i];
	}
}

wchar_t map::getMap()
{
	return *mapArray;
}

bool map::CheckWithRay(float playerx, float playery, float rads, int distance)
{
	int rayX = (playerx + (sinf(rads) * distance));
	int rayY = (playery + (cosf(rads) * distance));

	if (mapArray[(int)(rayX + ((size) * rayY))] == '#')
	{
		return true;
	}
	else
	{
		return false;
	}
}

float map::CheckWithRayAndTraceBack(float playerX, float playerY, float rads, int maxDistance)//Checks if each block is a wall and if it is traces the ray back to the start of the wall to get the distance
{
	float prevRayX = -1;
	float prevRayY = -1;
	float prevDistance = 0;

	for (int i = 0; i < maxDistance; i++)
	{
		float fDistance = (float)i;
		float rayX = (playerX + (sinf(rads) * fDistance));
		float rayY = (playerY + (cosf(rads) * fDistance));

		if (mapArray[(int)((int)rayX + ((size)*(int)rayY))] == '#')
		{
			while (fDistance > 0)
			{
				prevDistance = fDistance;
				fDistance -= 0.1f;

				rayX = (playerX + (sinf(rads) * fDistance));
				rayY = (playerY + (cosf(rads) * fDistance));

				if (mapArray[(int)((int)rayX + ((size)*(int)rayY))] != '#')
				{
					//return sqrt(pow(sinf(rads) * fDistance, 2) + pow(cosf(rads) * fDistance, 2));
					return prevDistance;
				}
			}
			return 0;
		}
	}
	return maxDistance;
}