#pragma once
#include <iterator>

static class map
{
private:
	static const int size = 20;
	static wchar_t mapArray[size * size];

public:
	static void buildMap();
	static wchar_t getMap();
	static bool CheckWithRay(float playerx, float playery, float rads, int distance);
	static float CheckWithRayAndTraceBack(float playerX, float playerY, float rads, int maxDistance);
};

