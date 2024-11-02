#include "player.h"

float player::GetPlayerXPos()
{
	return playerXPos;
}

float player::GetPlayerYPos()
{
	return playerYPos;
}

float player::GetPlayerRot()
{
	return playerRot;
}

void player::SetPlayerXPos(float value)
{
	playerXPos = value;
}

void player::SetPlayerYPos(float value)
{
	playerYPos = value;
}

void player::SetPlayerRot(float value)
{
	playerRot = value;
}

player::player()
{

}