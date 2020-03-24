#include "invaders.h"

#include "game_manager.h"

namespace MyGame{
namespace Invaders{
using namespace GameManager;

	Invader invaders[maxInvadersY][maxInvadersX];
	static float invaderTimer = 0;;
	void init(){
		
		invaderTimer = 0;

		for (int i = 0; i < maxInvadersY; i++)
		{
			for (int j = 0; j < maxInvadersX; j++)
			{
				invaders[i][j].body.width = 40;
				invaders[i][j].body.height = 30;
				invaders[i][j].pos.x = ((70 * j)) + invaders[i][j].body.width + 20;
				invaders[i][j].pos.y = 100 + (60 * i);
				invaders[i][j].body.x = invaders[i][j].pos.x - invaders[i][j].body.width / 2;
				invaders[i][j].body.y = invaders[i][j].pos.y - invaders[i][j].body.height / 2;
				invaders[i][j].speed.x = 100;
				invaders[i][j].speed.y = 100;
				invaders[i][j].active = true;
				invaders[i][j].color = WHITE;

				invaders[0][j].texture[0] = LoadTexture("res/invaders/invader3/invader3_1.png");
				invaders[0][j].texture[1] = LoadTexture("res/invaders/invader3/invader3_2.png");
				
				if (i >= 1 && i <= 2)
				{
					invaders[i][j].texture[0] = LoadTexture("res/invaders/invader2/invader2_1.png");
					invaders[i][j].texture[1] = LoadTexture("res/invaders/invader2/invader2_2.png");
				}

				if (i >= 3 && i <= 4)
				{
					invaders[i][j].texture[0] = LoadTexture("res/invaders/invader1/invader1_1.png");
					invaders[i][j].texture[1] = LoadTexture("res/invaders/invader1/invader1_2.png");
				}
			}
		}
	}

	void update() {

		invaderTimer += GetFrameTime();

		if (invaderTimer >= 2)
		{
			invaderTimer = 0;
		}

		for (int i = 0; i < maxInvadersY; i++)
		{
			for (int j = 0; j < maxInvadersX; j++)
			{
				//Body follows the texture
				invaders[i][j].body.x = invaders[i][j].pos.x - invaders[i][j].body.width / 2;
				invaders[i][j].body.y = invaders[i][j].pos.y - invaders[i][j].body.height / 2;

				//Invader Controls to mimic real movement
				if (IsKeyPressed(KEY_RIGHT))
				{
					invaders[i][j].pos.x += 20;
				}

				if (IsKeyPressed(KEY_UP))
				{
					invaders[i][j].pos.y -= 20;
				}

				if (IsKeyPressed(KEY_DOWN))
				{
					invaders[i][j].pos.y += 20;
				}

				if (IsKeyPressed(KEY_LEFT))
				{
					invaders[i][j].pos.x -= 20;
				}
			}
		}
	}

	void draw() {

		for (int i = 0; i < maxInvadersY; i++)
		{
			for (int j = 0; j < maxInvadersX; j++)
			{
				//DrawRectangleRec(invaders[i][j].body, invaders[i][j].color);

				if (invaderTimer < 1)
				{
					DrawTexture(invaders[i][j].texture[0], invaders[i][j].pos.x - invaders[i][j].texture[0].width / 2, invaders[i][j].pos.y - invaders[i][j].texture[0].height / 2, invaders[i][j].color);
				}
				if (invaderTimer >= 1)
				{
					DrawTexture(invaders[i][j].texture[1], invaders[i][j].pos.x - invaders[i][j].texture[1].width / 2, invaders[i][j].pos.y - invaders[i][j].texture[1].height / 2, invaders[i][j].color);
				}
			}
		}
	}

	void deInit() {

		for (int i = 0; i < maxInvadersY; i++)
		{
			for (int j = 0; j < maxInvadersX; j++)
			{
				UnloadTexture(invaders[i][j].texture[0]);
				UnloadTexture(invaders[i][j].texture[1]);
			}
		}
	}
}
}