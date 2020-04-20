#include "ufo.h"

#include "game_manager.h"

namespace MyGame {
namespace Ufo {
using namespace GameManager;

	UFO ufo;
	
	float ufoMovementTimer;
	float ufoTextureTimer;

	void init() {

		ufoMovementTimer = 0;
		ufoTextureTimer = 0;

		ufo.pos.x = 0;
		ufo.pos.y = 25;
		ufo.rec.width = 60;
		ufo.rec.height = 15;
		ufo.rec.x = ufo.pos.x - ufo.rec.width;
		ufo.rec.y = ufo.pos.y - ufo.rec.height / 2;
		ufo.speed = 200.0f;
		ufo.pointsToGive = 500;
		ufo.active = false;
		ufo.texture[0] = LoadTexture("res/assets/ufo/ufo1.png");
		ufo.texture[1] = LoadTexture("res/assets/ufo/ufo2.png");
		ufo.color = WHITE;
	}

	void update() {

		ufoMovementTimer += GetFrameTime();
		ufoTextureTimer += GetFrameTime();

		if (ufoMovementTimer >= 1.0f)
		{
			ufo.active = true;
		}

		if (ufoTextureTimer >= 0.2f)
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

		if (ufo.active)
		{
			if (ufoTextureTimer < 0.1f)
			{
				DrawTexture(ufo.texture[0], ufo.pos.x - ufo.texture[0].width / 2, ufo.pos.y - ufo.texture[0].height / 2, ufo.color);
			}
			else
			{
				DrawTexture(ufo.texture[1], ufo.pos.x - ufo.texture[1].width / 2, ufo.pos.y - ufo.texture[1].height / 2, ufo.color);
			}
		}
	}

	void deInit() {

		UnloadTexture(ufo.texture[0]);
		UnloadTexture(ufo.texture[1]);
	}
}
}