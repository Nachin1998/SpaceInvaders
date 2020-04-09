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

	static void initUFO();
	static void updateUFO();
	static void drawUFO();
	static void initWall();
	static void updateWall();
	static void drawWall();
	static void collisionManager();

	const int ufoMaxTextures = 2;
	const int MaxWalls = 4;
	bool paused;

	struct Wall {
		Rectangle rec;
		int lives;
		Vector2 pos;
		bool active;
		Color color;
	};
	static Wall walls[MaxWalls];

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
		paused = false;
		Player::init();
		Invaders::init();
		initUFO();
		initWall();
	}

	void update() {

		if (IsKeyPressed(KEY_P))
		{
			if (paused)
			{
				paused = false;
			}
			else
			{
				paused = true;
			}
		}


		if (!paused)
		{
			Player::update();
			Invaders::update();
			updateUFO();
			updateWall();
			collisionManager();

			if (Invaders::activeInvaderCounter == 1)
			{
				Invaders::maxTimer = 0.03f;
			}

			if (Invaders::activeInvaderCounter == 0)
			{
				//win
			}
		}
		
	}

	void draw() {

		Player::draw();
		Invaders::draw();

		drawUFO();
		drawWall();
		DrawCircle(GetMousePosition().x, GetMousePosition().y, 5, WHITE);

		if (paused)
		{
			DrawText("Paused", screenWidth / 2, screenHeight / 2, 100, WHITE);
		}
	}

	void deInit() {

		Player::deInit();
		Invaders::deInit();
		UnloadTexture(ufo.texture[0]);
		UnloadTexture(ufo.texture[1]);
	}
	
	void initUFO() {

		ufo.pos.x = 0;
		ufo.pos.y = 25;
		ufo.rec.width = 72;
		ufo.rec.height = 15;
		ufo.rec.x = ufo.pos.x - ufo.rec.width;
		ufo.rec.y = ufo.pos.y - ufo.rec.height / 2;
		ufo.speed = 200.0f;
		ufo.pointsToGive = 500;
		ufo.active = false;
		ufo.texture[0] = LoadTexture("res/textures/ufo/ufo1.png");
		ufo.texture[1] = LoadTexture("res/textures/ufo/ufo2.png");
		ufo.color = WHITE;
	}

	void updateUFO() {

		ufoMovementTimer += GetFrameTime();
		ufoTextureTimer += GetFrameTime();

		if (ufoMovementTimer >= 30.0f)
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

	void initWall() {

		for (int i = 0; i < MaxWalls; i++)
		{
			walls[i].rec.width = 100;
			walls[i].rec.height = 100;
			walls[i].pos.x = walls[i].rec.width + 13 + i *(screenWidth / MaxWalls);
			walls[i].pos.y = 700;
			walls[i].rec.x = walls[i].pos.x - walls[i].rec.width / 2;
			walls[i].rec.y = walls[i].pos.y - walls[i].rec.height / 2;
			walls[i].active = true;
			walls[i].lives = 5;
			walls[i].color = DARKGREEN;
		}
	}

	void updateWall() {

		for (int i = 0; i < MaxWalls; i++)
		{
			switch (walls[i].lives)
			{
			case 5:
				walls[i].color = DARKGREEN;
				break;
			case 4:
				walls[i].color = GREEN;
				break;
			case 3:
				walls[i].color = ORANGE;
				break;
			case 2:
				walls[i].color = YELLOW;
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

	void drawWall() {

		for (int i = 0; i < MaxWalls; i++)
		{
			if (walls[i].active)
			{
				DrawRectangleRec(walls[i].rec, walls[i].color);
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
						Invaders::maxTimer -= 0.01f;
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

		for (int i = 0; i < MaxWalls; i++)
		{
			if (walls[i].active)
			{
				if (CheckCollisionRecs(Player::bullet.rec, walls[i].rec))
				{
					counterFix++;

					if (counterFix > 1)
					{
						Player::bullet.active = false;
						walls[i].lives -= 1;
						walls[i].rec.width -= 10;
						walls[i].rec.height -= 10;
						counterFix = 0;
					}
				}

				if (CheckCollisionRecs(Invaders::bullet.rec, walls[i].rec))
				{
					counterFix++;

					if (counterFix > 1)
					{
						Invaders::bullet.active = false;
						walls[i].lives -= 1;
						walls[i].rec.width -= 10;
						walls[i].rec.height -= 10;
						counterFix = 0;
					}
				}
			}
		}
	}
}
}