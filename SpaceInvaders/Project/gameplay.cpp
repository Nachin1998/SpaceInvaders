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

	static void initBackground();
	static void updateBackground();
	static void drawBackground();
	static void initUFO();
	static void updateUFO();
	static void drawUFO();
	static void initWall();
	static void updateWall();
	static void drawWall();
	static void collisionManager();

	static const int ufoMaxassets = 2;
	static const int MaxWalls = 4;
	static const int MaxBackgroundassets = 8;
	bool paused;

	struct Background {
		Vector2 pos;
		Image image[MaxBackgroundassets];
		Texture2D texture[MaxBackgroundassets];
		float timer;
		float timerLimit;
	};
	static Background background;

	struct Wall {
		Rectangle rec;
		Texture2D texture[2];
		int lives;
		Vector2 pos;
		bool active;
		Color color;
	};
	static Wall walls[MaxWalls];

	struct UFO {
		Rectangle rec;
		Texture2D texture[ufoMaxassets];
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
	static float wallTextureTimer = 0;
	static int counterFix = 0;

	void init() {

		srand(time(NULL));
		counterFix = 0;
		paused = false;

		initBackground();
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
			updateBackground();
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

		drawBackground();
		Player::draw();
		Invaders::draw();

		drawUFO();
		drawWall();

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

	void initBackground() {

		background.pos.x = 0;
		background.pos.y = 0;
		background.timer = 0;
		background.timerLimit = 16;
		background.image[0] = LoadImage("res/assets/background/background_1.png");
		background.image[1] = LoadImage("res/assets/background/background_2.png");
		background.image[2] = LoadImage("res/assets/background/background_3.png");
		background.image[3] = LoadImage("res/assets/background/background_4.png");
		background.image[4] = LoadImage("res/assets/background/background_5.png");
		background.image[5] = LoadImage("res/assets/background/background_6.png");
		background.image[6] = LoadImage("res/assets/background/background_7.png");
		background.image[7] = LoadImage("res/assets/background/background_8.png");

		for (int i = 0; i < MaxBackgroundassets; i++)
		{
			background.texture[i] = LoadTextureFromImage(background.image[i]);
			UnloadImage(background.image[i]);
		}

	}

	void updateBackground() {

		background.timer += GetFrameTime();

		if (background.timer > background.timerLimit)
		{
			background.timer = 0;
		}
	}

	void drawBackground() {

		/*Almost works
		int timeToWait = 0;
		int textureCounter = 0;
		for (int i = 0; i < MaxBackgroundassets; i++)
		{
			if (background.timer > timeToWait && background.timer < timeToWait + 2)
			{
				DrawTexture(background.texture[textureCounter], background.pos.x, background.pos.y, WHITE);
			}
			else
			{
				timeToWait += 2;
				textureCounter++;
			}
		}*/
		if(background.timer < 2)
		{
			DrawTexture(background.texture[0], background.pos.x, background.pos.y, WHITE);
		}
		if (background.timer > 2 && background.timer < 4)
		{
			DrawTexture(background.texture[1], background.pos.x, background.pos.y, WHITE);
		}
		if (background.timer > 4 && background.timer < 6)
		{
			DrawTexture(background.texture[2], background.pos.x, background.pos.y, WHITE);
		}
		if (background.timer > 6 && background.timer < 8)
		{
			DrawTexture(background.texture[3], background.pos.x, background.pos.y, WHITE);
		}
		if (background.timer > 8 && background.timer < 10)
		{
			DrawTexture(background.texture[4], background.pos.x, background.pos.y, WHITE);
		}
		if (background.timer > 10 && background.timer < 12)
		{
			DrawTexture(background.texture[5], background.pos.x, background.pos.y, WHITE);
		}
		if (background.timer > 12 && background.timer < 14)
		{
			DrawTexture(background.texture[6], background.pos.x, background.pos.y, WHITE);
		}
		if (background.timer > 14 && background.timer < background.timerLimit)
		{
			DrawTexture(background.texture[7], background.pos.x, background.pos.y, WHITE);
		}
	}
	
	void initUFO() {

		ufoMovementTimer = 0;
		ufoTextureTimer = 0;

		ufo.pos.x = 0;
		ufo.pos.y = 25;
		ufo.rec.width = 72;
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

		wallTextureTimer = 0;

		for (int i = 0; i < MaxWalls; i++)
		{
			walls[i].rec.width = 130;
			walls[i].rec.height = 50;
			walls[i].pos.x = walls[i].rec.width - 18 + i *(screenWidth / MaxWalls);
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

	void updateWall() {

		wallTextureTimer += GetFrameTime();

		if (wallTextureTimer >= 1)
		{
			wallTextureTimer = 0;
		}

		for (int i = 0; i < MaxWalls; i++)
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

	void drawWall() {

		for (int i = 0; i < MaxWalls; i++)
		{
			if (walls[i].active)
			{
				//DrawRectangleRec(walls[i].rec, walls[i].color);

				if (wallTextureTimer < 0.5)
				{
					DrawTexture(walls[i].texture[0], walls[i].pos.x - walls[i].texture[0].width / 2, walls[i].pos.y - walls[i].texture[0].height / 2, walls[i].color);
				}
				else
				{
					DrawTexture(walls[i].texture[1], walls[i].pos.x - walls[i].texture[1].width / 2, walls[i].pos.y - walls[i].texture[1].height / 2, walls[i].color);
				}
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
						counterFix = 0;
					}
				}
			}
		}
	}
}
}