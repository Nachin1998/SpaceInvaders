#include "gameplay.h"

#include "raylib.h"
#include <iostream>
#include <time.h>

#include "game_manager.h"
#include "player.h"
#include "invaders.h"
#include "ufo.h"

#include "utility.h"

namespace MyGame {
namespace Gameplay {
using namespace GameManager;
using namespace UI;

	static void initBackground();
	static void updateBackground();
	static void drawBackground();
	static void initWall();
	static void updateWall();
	static void drawWall();
	static void initPauseMenu();
	static void updatePauseMenu();
	static void drawPauseMenu();
	static void collisionManager();
	static void gameOver();

	static const int maxWalls = 4;
	static const int maxWallsTextures = 2;
	static const int maxBackgroundTextures = 8;
	static bool paused;

	static Button pauseBackground;
	static Button resume;
	static Button restart;
	static Button toMenu;

	struct Background {
		Vector2 pos;
		Texture2D texture[maxBackgroundTextures];
		float timer;
		float timeToWait;
		float timerLimit;
	};
	static Background background;

	struct Wall {
		Rectangle rec;
		Texture2D texture[maxWallsTextures];
		int lives;
		Vector2 pos;
		bool active;
		Color color;
	};
	static Wall walls[maxWalls];

	static bool endGame;
	static bool win;
	static bool lose;

	static float wallTextureTimer = 0;
	static int counterFix = 0;

	void init() {

		srand(time(NULL));
		counterFix = 0;
		paused = false;

		initBackground();
		Player::init();
		Invaders::init();
		Ufo::init();
		initWall();
		initPauseMenu();
	}

	void update() {

		if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_P))
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
			Ufo::update();
			updateWall();
			collisionManager();

			if (Invaders::activeInvaderCounter == 1)
			{
				Invaders::maxTimer = 0.03f;
			}

			if (Invaders::activeInvaderCounter == 0)
			{
				gameOver();
			}
		}
		else 
		{
			updatePauseMenu();
		}

		if (Player::player.isDead || IsKeyPressed(KEY_R)) 
		{
			gameOver();
		}
	}

	void draw() {

		drawBackground();
		Player::draw();
		Invaders::draw();

		Ufo::draw();
		drawWall();

		if (paused)
		{
			drawPauseMenu();
		}
	}

	void deInit() {

		Player::deInit();
		Invaders::deInit();
		Ufo::deInit();
		
		for (int i = 0; i < maxBackgroundTextures; i++)
		{
			UnloadTexture(background.texture[i]);
		}

		for (int i = 0; i < maxWalls; i++)
		{
			for (int j = 0; j < maxWallsTextures; j++)
			{
				UnloadTexture(walls[i].texture[j]);
			}
		}
	}

	void initBackground() {

		background.pos.x = 0;
		background.pos.y = 0;
		background.timer = 0;
		background.timeToWait = 2;
		background.timerLimit = maxBackgroundTextures * background.timeToWait;

		background.texture[0] = LoadTexture("res/assets/background/pixelated/lvl4_1.png");
		background.texture[1] = LoadTexture("res/assets/background/pixelated/lvl4_2.png");
		background.texture[2] = LoadTexture("res/assets/background/pixelated/lvl4_3.png");
		background.texture[3] = LoadTexture("res/assets/background/pixelated/lvl4_4.png");
		background.texture[4] = LoadTexture("res/assets/background/pixelated/lvl4_5.png");
		background.texture[5] = LoadTexture("res/assets/background/pixelated/lvl4_6.png");
		background.texture[6] = LoadTexture("res/assets/background/pixelated/lvl4_7.png");
		background.texture[7] = LoadTexture("res/assets/background/pixelated/lvl4_8.png");
	}

	void updateBackground() {

		background.timer += GetFrameTime();

		if (background.timer > background.timerLimit)
		{
			background.timer = 0;
		}
	}

	void drawBackground() {

		
		if(background.timer < background.timeToWait)
		{
			DrawTexture(background.texture[0], background.pos.x, background.pos.y, WHITE);
		}
		else if (background.timer > background.timeToWait && background.timer < background.timeToWait + background.timeToWait)
		{
			DrawTexture(background.texture[1], background.pos.x, background.pos.y, WHITE);
		}
		else if (background.timer > background.timeToWait + background.timeToWait && background.timer < background.timeToWait + background.timeToWait * 2)
		{
			DrawTexture(background.texture[2], background.pos.x, background.pos.y, WHITE);
		}
		else if (background.timer > background.timeToWait + background.timeToWait * 2 && background.timer < background.timeToWait + background.timeToWait * 3)
		{
			DrawTexture(background.texture[3], background.pos.x, background.pos.y, WHITE);
		}
		else if (background.timer > background.timeToWait + background.timeToWait * 3 && background.timer < background.timeToWait + background.timeToWait * 4)
		{
			DrawTexture(background.texture[4], background.pos.x, background.pos.y, WHITE);
		}
		else if (background.timer > background.timeToWait + background.timeToWait * 4 && background.timer < background.timeToWait + background.timeToWait * 5)
		{
			DrawTexture(background.texture[5], background.pos.x, background.pos.y, WHITE);
		}
		else if (background.timer > background.timeToWait + background.timeToWait * 5 && background.timer < background.timeToWait + background.timeToWait * 6)
		{
			DrawTexture(background.texture[6], background.pos.x, background.pos.y, WHITE);
		}
		else if (background.timer > background.timeToWait + background.timeToWait * 6 && background.timer < background.timerLimit)
		{
			DrawTexture(background.texture[7], background.pos.x, background.pos.y, WHITE);
		}
	}

	void initWall() {

		wallTextureTimer = 0;

		for (int i = 0; i < maxWalls; i++)
		{
			walls[i].rec.width = 150;
			walls[i].rec.height = 50;
			walls[i].pos.x = walls[i].rec.width - 38 + i *(screenWidth / maxWalls);
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

	void drawWall() {

		for (int i = 0; i < maxWalls; i++)
		{
			if (walls[i].active)
			{
				DrawRectangleRec(walls[i].rec, walls[i].color);

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

	void initPauseMenu() {

		pauseBackground.rec.width = 350;
		pauseBackground.rec.height = 500;
		pauseBackground.rec.x = screenWidth / 2 - pauseBackground.rec.width / 2;
		pauseBackground.rec.y = screenHeight / 2 - pauseBackground.rec.height / 2;
		initButton(pauseBackground, pauseBackground.rec, 3, 0, DARKGREEN, GREEN);

		resume.rec.width = 270;
		resume.rec.height = 50;
		resume.rec.x = screenWidth / 2 - resume.rec.width / 2;
		resume.rec.y = 425 - resume.rec.height / 2;
		initButton(resume, resume.rec, 3, 30, BLANK, GREEN);

		restart.rec.width = 270;
		restart.rec.height = 50;
		restart.rec.x = screenWidth / 2 - restart.rec.width / 2;
		restart.rec.y = 525 - restart.rec.height / 2;
		initButton(restart, restart.rec, 3, 30, BLANK, GREEN);

		toMenu.rec.width = 270;
		toMenu.rec.height = 50;
		toMenu.rec.x = screenWidth / 2 - toMenu.rec.width / 2;
		toMenu.rec.y = 625 - toMenu.rec.height / 2;
		initButton(toMenu, toMenu.rec, 3, 25, BLANK, GREEN);
	}

	void updatePauseMenu() {

		Vector2 mousePos = GetMousePosition();

		updateButton(resume, BLANK, DARKGRAY);
		if (CheckCollisionPointRec(mousePos, resume.rec))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				paused = false;
			}
		}

		updateButton(restart, BLANK, DARKGRAY);
		if (CheckCollisionPointRec(mousePos, restart.rec))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				init();
			}
		}		

		updateButton(toMenu, BLANK, DARKGRAY);
		if (CheckCollisionPointRec(mousePos, toMenu.rec))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				init();
				GameManager::actualScene = GameManager::MainMenu;
			}
		}
	}

	void drawPauseMenu() {

		drawButton("", pauseBackground);
		drawProText("Paused", screenWidth / 2, screenHeight / 2 - 200, 60, GREEN);
		drawButton("Resume", resume);
		drawButton("Play Again", restart);
		drawButton("Back to Main Menu", toMenu);
	}

	void collisionManager() {

		for (int i = 0; i < Invaders::maxInvadersY; i++)
		{
			for (int j = 0; j < Invaders::maxInvadersX; j++)
			{
				if (Invaders::invaders[i][j].active && Player::bullet.active)
				{
					if (CheckCollisionRecs(Player::bullet.rec, Invaders::invaders[i][j].body))
					{
						Invaders::activeInvaderCounter--;

						Invaders::invaders[i][j].active = false;
						Player::bullet.active = false;
						Invaders::maxTimer -= 0.01f;
						Player::player.points += Invaders::invaders[i][j].pointsToGive;

						std::cout << "Puntos: " << Player::player.points << std::endl;
						std::cout << "Invaders active: "<<Invaders::activeInvaderCounter << std::endl;
					}
				}

				if (Invaders::invaders[i][j].active && Player::player.lives > 0)
				{
					if (CheckCollisionRecs(Player::player.body, Invaders::invaders[i][j].body))
					{
						gameOver();
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

		if (Ufo::ufo.active)
		{
			if (CheckCollisionRecs(Player::bullet.rec, Ufo::ufo.rec))
			{
				Ufo::ufo.active = false;
				Ufo::ufoActivationTimer = 0;
				Player::bullet.active = false;
				Player::player.points += Ufo::ufo.pointsToGive;
			}
		}

		if (Ufo::laser.active)
		{
			if (CheckCollisionRecs(Ufo::laser.rec, Player::player.body))
			{
				counterFix++;
				if (counterFix > 20)
				{
					Player::player.lives -= 1;
					std::cout << Player::player.lives << std::endl;
					counterFix = 0;
				}
			}
		}

		for (int i = 0; i < maxWalls; i++)
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

	void gameOver() {

		Gameplay::deInit();
		actualScene = GameOver;
	}
}
}