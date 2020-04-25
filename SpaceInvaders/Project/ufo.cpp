#include "ufo.h"

#include <iostream>
#include <time.h>

#include "game_manager.h"

namespace MyGame {
namespace Ufo {
using namespace GameManager;

	static void drawUFOTextures(Texture2D textures[]);

	enum UFOState {
		Idle,
		Charging,
		Attacking
	};
	static UFOState ufoState = Idle;

	UFO ufo;
	Laser laser;

	float ufoActivationTimer;

	static float ufoTextureTimer;
	static float ufoMaxTextureTimer;

	static float ufoChargingTimer;
	static float ufoMaxChargingTimer;

	static float ufoAttackTimer;
	static float ufoMaxAttackTimer;

	static int randomPos;
	static float laserPosFix;

	void init() {

		srand(time(NULL));

		ufoActivationTimer = 0;

		ufoTextureTimer = 0;
		ufoMaxTextureTimer = 0.6f;

		ufoChargingTimer = 0;
		ufoMaxChargingTimer = 0;

		ufoAttackTimer = 0;
		ufoMaxAttackTimer = 2.5;
		laserPosFix = 3.0f;

		ufo.pos.x = 0;
		ufo.pos.y = 35;
		ufo.rec.width = 60;
		ufo.rec.height = 15;
		ufo.rec.x = ufo.pos.x - ufo.rec.width;
		ufo.rec.y = ufo.pos.y - ufo.rec.height / 2;
		ufo.speed = 160.0f;
		ufo.pointsToGive = 500;
		ufo.active = false;
		ufo.idleTexture[0] = LoadTexture("res/assets/ufo/ufo_idle_1.png");
		ufo.idleTexture[1] = LoadTexture("res/assets/ufo/ufo_idle_2.png");
		ufo.idleTexture[2] = LoadTexture("res/assets/ufo/ufo_idle_3.png");
		ufo.idleTexture[3] = LoadTexture("res/assets/ufo/ufo_idle_4.png");
		ufo.idleTexture[4] = LoadTexture("res/assets/ufo/ufo_idle_5.png");
		ufo.idleTexture[5] = LoadTexture("res/assets/ufo/ufo_idle_6.png");
		ufo.chargingTexture[0] = LoadTexture("res/assets/ufo/ufo_charging_1.png");
		ufo.chargingTexture[1] = LoadTexture("res/assets/ufo/ufo_charging_2.png");
		ufo.chargingTexture[2] = LoadTexture("res/assets/ufo/ufo_charging_3.png");
		ufo.chargingTexture[3] = LoadTexture("res/assets/ufo/ufo_charging_4.png");
		ufo.chargingTexture[4] = LoadTexture("res/assets/ufo/ufo_charging_5.png");
		ufo.chargingTexture[5] = LoadTexture("res/assets/ufo/ufo_charging_6.png");
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
		laser.texture.width *= 2;
		laser.texture.height *= 5;
		laser.active = false;
		laser.color = WHITE;
	}

	void update() {

		ufoActivationTimer += GetFrameTime();
		ufoTextureTimer += GetFrameTime();

		ufo.rec.x = ufo.pos.x - ufo.rec.width / 2;
		ufo.rec.y = ufo.pos.y - ufo.rec.height / 2;
		laser.pos.x = ufo.pos.x + laserPosFix;
		laser.rec.x = laser.pos.x - laser.rec.width / 2;

		if (ufoTextureTimer >= ufoMaxTextureTimer)
		{
			ufoTextureTimer = 0;
		}

		if (ufoActivationTimer >= 1.0f)
		{
			ufo.active = true;
		}
		else
		{
			randomPos = rand() % 2;
			ufoMaxChargingTimer = rand() % 2 + 1;
		}

		if (ufoState == Attacking)
		{
			laser.active = true;
		}
		else
		{
			laser.active = false;
		}

		if (ufo.active)
		{
			ufoChargingTimer += GetFrameTime();

			if (randomPos == 0)
			{
				ufo.pos.x += ufo.speed * GetFrameTime();
				laserPosFix = 2.9f;
				if (ufo.pos.x - ufo.rec.width / 2 > screenWidth)
				{
					ufo.active = false;
					ufoActivationTimer = 0;
				}
			}

			if (randomPos == 1)
			{
				ufo.pos.x -= ufo.speed * GetFrameTime();
				laserPosFix = -2.9f;
				if (ufo.pos.x + ufo.rec.width / 2 < 0)
				{
					ufo.active = false;
					ufoActivationTimer = 0;
				}
			}

			if (ufoChargingTimer < ufoMaxChargingTimer)
			{
				ufoState = Idle;
			}
			if (ufoChargingTimer > ufoMaxChargingTimer && ufoChargingTimer < ufoMaxChargingTimer * 2)
			{
				ufoState = Charging;
			}
			if (ufoChargingTimer > ufoMaxChargingTimer * 2 && ufoChargingTimer < ufoMaxChargingTimer * 3.5)
			{
				ufoState = Attacking;
			}
			if (ufoChargingTimer > ufoMaxChargingTimer * 3.5)
			{
				ufoState = Idle;
			}
		}

		if (!ufo.active)
		{
			if (randomPos == 0)
			{
				ufo.pos.x = 0 - ufo.rec.width / 2;
			}

			if (randomPos == 1)
			{
				ufo.pos.x = screenWidth + ufo.rec.width / 2;
			}

			ufoChargingTimer = 0;
		}
	}


	void draw() {

		//DrawRectangleRec(ufo.rec, ufo.color);
		//DrawRectangleRec(laser.rec, WHITE);

		if (laser.active)
		{
			DrawTexture(laser.texture, laser.pos.x - laser.texture.width / 2, laser.pos.y, laser.color);
		}

		if (ufo.active)
		{
			switch (ufoState)
			{
			case Idle:
				drawUFOTextures(ufo.idleTexture);
				break;

			case Charging:
				drawUFOTextures(ufo.chargingTexture);
				break;

			case Attacking:
				drawUFOTextures(ufo.attackingTexture);
				break;

			default:
				break;
			}
		}
	}

	void deInit() {

		for (int i = 0; i < ufoMaxTextures; i++)
		{
			UnloadTexture(ufo.idleTexture[i]);
			UnloadTexture(ufo.chargingTexture[i]);
			UnloadTexture(ufo.attackingTexture[i]);
		}
		UnloadTexture(laser.texture);
	}

	void drawUFOTextures(Texture2D textures[]) {

		if (ufoTextureTimer < 0.1f)
		{
			DrawTexture(textures[0], ufo.pos.x - textures[0].width / 2, ufo.pos.y - textures[0].height / 2, ufo.color);
		}
		else if (ufoTextureTimer > 0.1f && ufoTextureTimer < 0.2f)
		{
			DrawTexture(textures[1], ufo.pos.x - textures[1].width / 2, ufo.pos.y - textures[1].height / 2, ufo.color);
		}
		else if (ufoTextureTimer > 0.2f && ufoTextureTimer < 0.3f)
		{
			DrawTexture(textures[2], ufo.pos.x - textures[2].width / 2, ufo.pos.y - textures[2].height / 2, ufo.color);
		}
		else if (ufoTextureTimer > 0.3f && ufoTextureTimer < 0.4f)
		{
			DrawTexture(textures[3], ufo.pos.x - textures[3].width / 2, ufo.pos.y - textures[3].height / 2, ufo.color);
		}
		else if (ufoTextureTimer > 0.4f && ufoTextureTimer < 0.5f)
		{
			DrawTexture(textures[4], ufo.pos.x - textures[4].width / 2, ufo.pos.y - textures[4].height / 2, ufo.color);
		}
		else if (ufoTextureTimer > 0.5f && ufoTextureTimer < ufoMaxTextureTimer)
		{
			DrawTexture(textures[5], ufo.pos.x - textures[5].width / 2, ufo.pos.y - textures[5].height / 2, ufo.color);
		}
	}
}
}