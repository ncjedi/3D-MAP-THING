#pragma once
class player
{
private:
	float playerXPos = 2.0f;
	float playerYPos = 2.0f;
	float playerRot = 0.0f;

public:
	float GetPlayerXPos();
	float GetPlayerYPos();
	float GetPlayerRot();

	void SetPlayerXPos(float value);
	void SetPlayerYPos(float value);
	void SetPlayerRot(float value);
	player();
};

