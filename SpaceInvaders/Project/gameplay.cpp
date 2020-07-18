#include "gameplay.h"

#include "raylib.h"
#include <iostream>
#include <time.h>

#include "game_manager.h"
#include "player.h"
#include "invaders.h"
#include "ufo.h"
#include "wall.h"
#include "pause_menu.h"

#include "utility.h"

namespace MyGame {
namespace Gameplay {
using namespace GameManager;
using namespace UI;

	static void initBackground();
	static void updateBackground();
	static void drawBackground(int actualLevel);
	static void collisionManager();
	static void gameOver();

	static const int maxLevels = 4;
	static const int maxBackgroundTextures = 8;

	bool paused = false;
	
	Levels level = One;

	struct Background {
		Vector2 pos;
		Texture2D texture[maxLevels][maxBackgroundTextures];
		float timer;
		float timeToWait;
		float timerLimit;
	};
	static Background background;

	static Sound hit;

	static bool endGame;

	static int counterFix = 0;

	void init() {

		srand(static_cast<int>(time(NULL)));
		counterFix = 0;
		paused = false;

		hit = LoadSound("res/sounds/hit.ogg");
		SetSoundVolume(hit, 1);

		initBackground();
		Player::init();
		Invaders::init();
		Ufo::init();
		Wall::init();
		PauseMenu::init();
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
			Wall::update();
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
			PauseMenu::update();
		}

		if (Player::player.isDead || IsKeyPressed(KEY_R)) 
		{
			gameOver();
		}

		switch (level)
		{
		case One:
			Ufo::timeUntillActive = 17.5f;
			break;
		case Two:
			Ufo::timeUntillActive = 15.0f;
			break;
		case Three:
			Ufo::timeUntillActive = 12.5f;
			break;
		case Four:
			Ufo::timeUntillActive = 10.0f;
			break;
		default:
			break;
		}
	}

	void draw() {

		switch (level)
		{
		case One:
			drawBackground(0);
			break;
		case Two:
			drawBackground(1);
			break;
		case Three:
			drawBackground(2);
			break;
		case Four:
			drawBackground(3);
			break;
		default:
			break;
		}
		
		Player::draw();
		Invaders::draw();

		Ufo::draw();
		Wall::draw();

		if (paused)
		{
			PauseMenu::draw();
		}
	}

	void deInit() {

		Player::deInit();
		Invaders::deInit();
		Ufo::deInit();
		Wall::deInit();

		for (int i = 0; i < maxLevels; i++)
		{
			for (int j = 0; j < maxBackgroundTextures; j++)
			{
				UnloadTexture(background.texture[i][j]);
			}
		}				
	}

	void initBackground() {

		background.pos.x = 0;
		background.pos.y = 0;
		background.timer = 0;
		background.timeToWait = 2;
		background.timerLimit = maxBackgroundTextures * background.timeToWait;

		background.texture[0][0] = LoadTexture("res/assets/background/Level1/lvl1_1.png");
		background.texture[0][1] = LoadTexture("res/assets/background/Level1/lvl1_2.png");
		background.texture[0][2] = LoadTexture("res/assets/background/Level1/lvl1_3.png");
		background.texture[0][3] = LoadTexture("res/assets/background/Level1/lvl1_4.png");
		background.texture[0][4] = LoadTexture("res/assets/background/Level1/lvl1_5.png");
		background.texture[0][5] = LoadTexture("res/assets/background/Level1/lvl1_6.png");
		background.texture[0][6] = LoadTexture("res/assets/background/Level1/lvl1_7.png");
		background.texture[0][7] = LoadTexture("res/assets/background/Level1/lvl1_8.png");


		background.texture[1][0] = LoadTexture("res/assets/background/Level2/lvl2_1.png");
		background.texture[1][1] = LoadTexture("res/assets/background/Level2/lvl2_2.png");
		background.texture[1][2] = LoadTexture("res/assets/background/Level2/lvl2_3.png");
		background.texture[1][3] = LoadTexture("res/assets/background/Level2/lvl2_4.png");
		background.texture[1][4] = LoadTexture("res/assets/background/Level2/lvl2_5.png");
		background.texture[1][5] = LoadTexture("res/assets/background/Level2/lvl2_6.png");
		background.texture[1][6] = LoadTexture("res/assets/background/Level2/lvl2_7.png");
		background.texture[1][7] = LoadTexture("res/assets/background/Level2/lvl2_8.png");


		background.texture[2][0] = LoadTexture("res/assets/background/Level3/lvl3_1.png");
		background.texture[2][1] = LoadTexture("res/assets/background/Level3/lvl3_2.png");
		background.texture[2][2] = LoadTexture("res/assets/background/Level3/lvl3_3.png");
		background.texture[2][3] = LoadTexture("res/assets/background/Level3/lvl3_4.png");
		background.texture[2][4] = LoadTexture("res/assets/background/Level3/lvl3_5.png");
		background.texture[2][5] = LoadTexture("res/assets/background/Level3/lvl3_6.png");
		background.texture[2][6] = LoadTexture("res/assets/background/Level3/lvl3_7.png");
		background.texture[2][7] = LoadTexture("res/assets/background/Level3/lvl3_8.png");


		background.texture[3][0] = LoadTexture("res/assets/background/Level4/lvl4_1.png");
		background.texture[3][1] = LoadTexture("res/assets/background/Level4/lvl4_2.png");
		background.texture[3][2] = LoadTexture("res/assets/background/Level4/lvl4_3.png");
		background.texture[3][3] = LoadTexture("res/assets/background/Level4/lvl4_4.png");
		background.texture[3][4] = LoadTexture("res/assets/background/Level4/lvl4_5.png");
		background.texture[3][5] = LoadTexture("res/assets/background/Level4/lvl4_6.png");
		background.texture[3][6] = LoadTexture("res/assets/background/Level4/lvl4_7.png");
		background.texture[3][7] = LoadTexture("res/assets/background/Level4/lvl4_8.png");
	}

	void updateBackground() {

		background.timer += GetFrameTime();

		if (background.timer > background.timerLimit)
		{
			background.timer = 0;
		}
	}

	void drawBackground(int activeLevel) {

		
		if(background.timer < background.timeToWait)
		{
			DrawTexture(background.texture[activeLevel][0], static_cast<int>(background.pos.x), static_cast<int>(background.pos.y), WHITE);
		}
		else if (background.timer > background.timeToWait && background.timer < background.timeToWait + background.timeToWait)
		{
			DrawTexture(background.texture[activeLevel][1], static_cast<int>(background.pos.x), static_cast<int>(background.pos.y), WHITE);
		}
		else if (background.timer > background.timeToWait + background.timeToWait && background.timer < background.timeToWait + background.timeToWait * 2)
		{
			DrawTexture(background.texture[activeLevel][2], static_cast<int>(background.pos.x), static_cast<int>(background.pos.y), WHITE);
		}
		else if (background.timer > background.timeToWait + background.timeToWait * 2 && background.timer < background.timeToWait + background.timeToWait * 3)
		{
			DrawTexture(background.texture[activeLevel][3], static_cast<int>(background.pos.x), static_cast<int>(background.pos.y), WHITE);
		}
		else if (background.timer > background.timeToWait + background.timeToWait * 3 && background.timer < background.timeToWait + background.timeToWait * 4)
		{
			DrawTexture(background.texture[activeLevel][4], static_cast<int>(background.pos.x), static_cast<int>(background.pos.y), WHITE);
		}
		else if (background.timer > background.timeToWait + background.timeToWait * 4 && background.timer < background.timeToWait + background.timeToWait * 5)
		{
			DrawTexture(background.texture[activeLevel][5], static_cast<int>(background.pos.x), static_cast<int>(background.pos.y), WHITE);
		}
		else if (background.timer > background.timeToWait + background.timeToWait * 5 && background.timer < background.timeToWait + background.timeToWait * 6)
		{
			DrawTexture(background.texture[activeLevel][6], static_cast<int>(background.pos.x), static_cast<int>(background.pos.y), WHITE);
		}
		else if (background.timer > background.timeToWait + background.timeToWait * 6 && background.timer < background.timerLimit)
		{
			DrawTexture(background.texture[activeLevel][7], static_cast<int>(background.pos.x), static_cast<int>(background.pos.y), WHITE);
		}
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
						PlaySound(hit);
						Invaders::activeInvaderCounter--;

						Invaders::invaders[i][j].active = false;
						Player::bullet.active = false;
						Invaders::maxTimer -= 0.01f;
						Player::player.points += Invaders::invaders[i][j].pointsToGive;
					}
				}

				if (Invaders::invaders[i][j].active)
				{
					if (CheckCollisionRecs(Player::player.body, Invaders::invaders[i][j].body))
					{
						Player::player.isDead = true;
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
				counterFix = 0;
			}
		}

		if (Ufo::ufo.active)
		{
			if (CheckCollisionRecs(Player::bullet.rec, Ufo::ufo.rec))
			{
				PlaySound(hit);
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

		for (int i = 0; i < Wall::maxWalls; i++)
		{
			if (Wall::walls[i].active)
			{
				if (CheckCollisionRecs(Player::bullet.rec, Wall::walls[i].rec))
				{
					counterFix++;

					if (counterFix > 1)
					{
						Player::bullet.active = false;
						Wall::walls[i].lives -= 1;
						counterFix = 0;
					}
				}

				if (CheckCollisionRecs(Invaders::bullet.rec, Wall::walls[i].rec))
				{
					counterFix++;

					if (counterFix > 1)
					{
						Invaders::bullet.active = false;
						Wall::walls[i].lives -= 1;
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