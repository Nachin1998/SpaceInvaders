#include "ufo.h"

#include "game_manager.h"

namespace MyGame {
namespace Ufo {
using namespace GameManager;

	UFO ufo;
	Laser laser;
	
	float ufoMovementTimer;
	float ufoTextureTimer;
	float ufoMaxTextureTimer;

	void init() {

		ufoMovementTimer = 0;
		ufoTextureTimer = 0;
		ufoMaxTextureTimer = 0.6f;

		ufo.pos.x = 0;
		ufo.pos.y = 35;
		ufo.rec.width = 60;
		ufo.rec.height = 15;
		ufo.rec.x = ufo.pos.x - ufo.rec.width;
		ufo.rec.y = ufo.pos.y - ufo.rec.height / 2;
		ufo.speed = 200.0f;
		ufo.pointsToGive = 500;
		ufo.active = false;
		ufo.idleTexture[0] = LoadTexture("res/assets/ufo/ufo_idle_1.png");
		ufo.idleTexture[1] = LoadTexture("res/assets/ufo/ufo_idle_2.png");
		ufo.idleTexture[2] = LoadTexture("res/assets/ufo/ufo_idle_3.png");
		ufo.idleTexture[3] = LoadTexture("res/assets/ufo/ufo_idle_4.png");
		ufo.idleTexture[4] = LoadTexture("res/assets/ufo/ufo_idle_5.png");
		ufo.idleTexture[5] = LoadTexture("res/assets/ufo/ufo_idle_6.png");
		ufo.attackingTexture[0] = LoadTexture("res/assets/ufo/ufo_attacking_1.png");
		ufo.attackingTexture[1] = LoadTexture("res/assets/ufo/ufo_attacking_2.png");
		ufo.attackingTexture[2] = LoadTexture("res/assets/ufo/ufo_attacking_3.png");
		ufo.attackingTexture[3] = LoadTexture("res/assets/ufo/ufo_attacking_4.png");
		ufo.attackingTexture[4] = LoadTexture("res/assets/ufo/ufo_attacking_5.png");
		ufo.attackingTexture[5] = LoadTexture("res/assets/ufo/ufo_attacking_6.png");
		ufo.color = WHITE;

		laser.rec.width = 46;
		laser.rec.height = 965;
		laser.pos.x = ufo.pos.x;
		laser.pos.y = ufo.pos.y;
		laser.rec.x = laser.pos.x - laser.rec.width / 2;
		laser.rec.y = laser.pos.y;
		laser.texture = LoadTexture("res/assets/ufo/laserbeam.png");
		laser.texture.height *= 3;
		laser.active = false;
		laser.color = WHITE;
	}

	void update() {

		ufoMovementTimer += GetFrameTime();
		ufoTextureTimer += GetFrameTime();
		laser.pos.x = ufo.pos.x + 3;
		laser.rec.x = laser.pos.x - laser.rec.width / 2;

		if (ufoMovementTimer >= 1.0f)
		{
			ufo.active = true;
		}

		if (ufoTextureTimer >= ufoMaxTextureTimer)
		{
			ufoTextureTimer = 0;
		}
		
		ufo.rec.x = ufo.pos.x - ufo.rec.width / 2;
		ufo.rec.y = ufo.pos.y - ufo.rec.height / 2;

		if (ufo.active)
		{
			ufo.pos.x += ufo.speed * GetFrameTime();

			if (ufo.pos.x - ufo.rec.width / 2 > screenWidth)
			{
				ufo.active = false;
				ufoMovementTimer = 0;
			}
		}
		else
		{
			ufo.pos.x = 0 - ufo.rec.width / 2;
		}
	}

	void draw() {

		DrawRectangleRec(ufo.rec, ufo.color);
		//DrawTexture(laser.texture, laser.pos.x - laser.texture.width / 2, laser.pos.y, laser.color);
		DrawRectangleRec(laser.rec, WHITE);

		if (ufo.active)
		{
			if (ufoTextureTimer < 0.1f)
			{
				DrawTexture(ufo.idleTexture[0], ufo.pos.x - ufo.idleTexture[0].width / 2, ufo.pos.y - ufo.idleTexture[0].height / 2, ufo.color);
			}
			else if(ufoTextureTimer > 0.1f && ufoTextureTimer < 0.2f)
			{
				DrawTexture(ufo.idleTexture[1], ufo.pos.x - ufo.idleTexture[1].width / 2, ufo.pos.y - ufo.idleTexture[1].height / 2, ufo.color);
			}
			else if (ufoTextureTimer > 0.2f && ufoTextureTimer < 0.3f)
			{
				DrawTexture(ufo.idleTexture[2], ufo.pos.x - ufo.idleTexture[2].width / 2, ufo.pos.y - ufo.idleTexture[2].height / 2, ufo.color);
			}
			else if (ufoTextureTimer > 0.3f && ufoTextureTimer < 0.4f)
			{
				DrawTexture(ufo.idleTexture[3], ufo.pos.x - ufo.idleTexture[3].width / 2, ufo.pos.y - ufo.idleTexture[3].height / 2, ufo.color);
			}
			else if (ufoTextureTimer > 0.4f && ufoTextureTimer < 0.5f)
			{
				DrawTexture(ufo.idleTexture[4], ufo.pos.x - ufo.idleTexture[4].width / 2, ufo.pos.y - ufo.idleTexture[4].height / 2, ufo.color);
			}
			else if (ufoTextureTimer > 0.5f && ufoTextureTimer < ufoMaxTextureTimer)
			{
				DrawTexture(ufo.idleTexture[5], ufo.pos.x - ufo.idleTexture[5].width / 2, ufo.pos.y - ufo.idleTexture[5].height / 2, ufo.color);
			}
		}
	}

	void deInit() {

		for (int i = 0; i < ufoMaxTextures; i++)
		{
			UnloadTexture(ufo.idleTexture[i]);
			UnloadTexture(ufo.attackingTexture[i]);
		}
		UnloadTexture(laser.texture);
	}
}
}