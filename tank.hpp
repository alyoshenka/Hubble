#pragma once

#include "raylib.h"
#include "colors.h"

class tank
{
public:

	void update(float frameTime)
	{

	}

	void draw()
	{
		DrawText("72f", 480, 15, 25, A_PURPLE_1);
		DrawText("85%", 530, 15, 25, A_PURPLE_1);
		DrawRectangleRec(Rectangle{ 590, 15, 25, 25 }, A_PURPLE_2);
	}
};
