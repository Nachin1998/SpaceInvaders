#include "gameplay.h"

#include "raylib.h"
#include <iostream>
#include <time.h>

#include "game_manager.h"
#include "player.h"
#include "invaders.h"

namespace MyGame {
namespace Gameplay {
using namespace GameManager;

	static void updateUFO();
	static void drawUFO();
	static void collisionManager();

	const int ufoMaxTextures = 2;
	static int randLocation;

	struct UFO {
		Rectangle rec;
		Texture2D texture[ufoMaxTextures];
		Vector2 pos;
		float speed;
		int pointsToGive;
		bool active;
		Color color;
	};

	static UFO ufo;

	static bool win;
	static bool lose;

	static float ufoMovementTimer = 0;
	static float ufoTextureTimer = 0;
	static int counterFix = 0;

	void init() {

		srand(time(0));
		counterFix = 0;
		ufoMovementTimer = 0;
		ufoTextureTimer = 0;

		Player::init();
		Invaders::init();

		ufo.pos.x = 0;
		ufo.pos.y = 25;
		ufo.rec.width = 72;
		ufo.rec.height = 5;
		ufo.rec.x = ufo.pos.x - ufo.rec.width;
		ufo.rec.y = ufo.pos.y - ufo.rec.height / 2;
		ufo.speed = 200.0f;
		ufo.pointsToGive = 500;
		ufo.active = false;
		ufo.texture[0] = LoadTexture("res/textures/ufo/ufo1.png");
		ufo.texture[1] = LoadTexture("res/textures/ufo/ufo2.png");
		ufo.color = WHITE;
	}

	void update() {

		Player::update();
		Invaders::update();

		updateUFO();
		collisionManager();
	}

	void draw() {

		Player::draw();
		Invaders::draw();

		drawUFO();
	}

	void deInit() {

		Player::deInit();
		Invaders::deInit();
	}

	void updateUFO() {

		ufoMovementTimer += GetFrameTime();
		ufoTextureTimer += GetFrameTime();

		if (ufoMovementTimer >= 30)
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
		}
		else
		{
			ufo.pos.x = 0 - ufo.rec.width / 2;
		}

		if (ufo.pos.x - ufo.rec.width / 2 > screenWidth)
		{
			ufo.active = false;
			ufoMovementTimer = 0;
		}
	}

	void drawUFO() {

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

	void collisionManager() {

		for (int i = 0; i < Invaders::maxInvadersY; i++)
		{
			for (int j = 0; j < Invaders::maxInvadersX; j++)
			{
				if (CheckCollisionRecs(Player::bullet.rec, Invaders::invaders[i][j].body))
				{
					if (Invaders::invaders[i][j].active && Player::bullet.active)
					{
						Invaders::activeInvaderCounter--;

						Invaders::invaders[i][j].active = false;
						Player::bullet.active = false;

						Player::player.points += Invaders::invaders[i][j].pointsToGive;

						std::cout << "Puntos: "<<Player::player.points << std::endl;
						std::cout << "Invaders active: "<<Invaders::activeInvaderCounter << std::endl;
					}
				}
			}
		}

		if (CheckCollisionRecs(Player::bullet.rec, Invaders::bullet.rec))
		{
			if (Player::bullet.active)
			{
				Invaders::bullet.active = false;
				Player::bullet.active = false;
			}
		}

		if (CheckCollisionRecs(Invaders::bullet.rec, Player::player.body))
		{
			counterFix++;
			
			if (counterFix > 1)
			{
				Invaders::bullet.active = false;
				Player::player.lives -= 1;
				std::cout << "Player lives: " << Player::player.lives << std::endl;
				counterFix = 0;
			}
		}

		if (CheckCollisionRecs(Player::bullet.rec, ufo.rec))
		{
			ufo.active = false;
			ufoMovementTimer = 0;
			Player::bullet.active = false;
			Player::player.points += ufo.pointsToGive;
		}
	}
}
}