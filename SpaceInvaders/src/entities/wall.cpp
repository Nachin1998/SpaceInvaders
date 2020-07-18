#include "wall.h"

#include "managers\game_manager.h"

namespace MyGame {
namespace Wall {
using namespace GameManager;

	float wallTextureTimer = 0;
	Wall walls[maxWalls];
	void init() {

		wallTextureTimer = 0;

		for (int i = 0; i < maxWalls; i++)
		{
			walls[i].rec.width = 150;
			walls[i].rec.height = 50;
			walls[i].pos.x = walls[i].rec.width - 38 + i * (screenWidth / maxWalls);
			walls[i].pos.y = 700;
			walls[i].rec.x = walls[i].pos.x - walls[i].rec.width / 2;
			walls[i].rec.y = walls[i].pos.y - walls[i].rec.height / 2;
			walls[i].texture[0] = LoadTexture("res/assets/wall/forcefield_1.png");
			walls[i].texture[1] = LoadTexture("res/assets/wall/forcefield_2.png");
			walls[i].active = true;
			walls[i].lives = 4;
			walls[i].color = GREEN;
		}
	}

	void update() {

		wallTextureTimer += GetFrameTime();

		if (wallTextureTimer >= 1)
		{
			wallTextureTimer = 0;
		}

		for (int i = 0; i < maxWalls; i++)
		{
			walls[i].rec.x = walls[i].pos.x - walls[i].rec.width / 2;
			walls[i].rec.y = walls[i].pos.y - walls[i].rec.height / 2;

			switch (walls[i].lives)
			{
			case 4:
				walls[i].color = SKYBLUE;
				break;
			case 3:
				walls[i].color = GREEN;
				break;
			case 2:
				walls[i].color = BROWN;
				break;
			case 1:
				walls[i].color = RED;
				break;
			case 0:
				walls[i].active = false;
				break;
			default:
				break;
			}
		}
	}

	void draw() {

		for (int i = 0; i < maxWalls; i++)
		{
			if (walls[i].active)
			{
				DrawRectangleRec(walls[i].rec, walls[i].color);

				if (wallTextureTimer < 0.5)
				{
					DrawTexture(walls[i].texture[0], static_cast<int>(walls[i].pos.x - walls[i].texture[0].width / 2), static_cast<int>(walls[i].pos.y - walls[i].texture[0].height / 2), walls[i].color);
				}
				else
				{
					DrawTexture(walls[i].texture[1], static_cast<int>(walls[i].pos.x - walls[i].texture[1].width / 2), static_cast<int>(walls[i].pos.y - walls[i].texture[1].height / 2), walls[i].color);
				}
			}
		}
	}

	void deInit() {

		for (int i = 0; i < maxWalls; i++)
		{
			for (int j = 0; j < maxWallsTextures; j++)
			{
				UnloadTexture(walls[i].texture[j]);
			}
		}
	}
}
}