#include "invaders.h"

#include <iostream>
#include <string>
#include <ctime>

#include "managers\game_manager.h"
#include "utility\utility.h"

namespace MyGame{
namespace Invaders{
using namespace GameManager;
	
	static void InitInvader();
	static void UpdateInvader();
	static void DrawInvader();
	static void InitBullet();
	static void UpdateBullet();
	static void bulletRespawn();
	static void DrawBullet();

	static void DeInitInvader();
	static void DeInitBullet();

	enum InvaderMovement {
		Horizontal,
		Vertical,
	};
	static InvaderMovement actualMovement;

	Bullet bullet;

	Invader invaders[maxInvadersY][maxInvadersX];

	static int randX;
	static int randY;

	static bool goingRight;
	static bool goingLeft;
	static bool changeMovementTexture = false;
	static float invaderMovementTimer;
	static float bulletTimer;

	int activeInvaderCounter;
	float maxTimer;
	
	void Init(){
		
		srand(static_cast<int>(time(NULL)));
		randX = rand() % maxInvadersX;
		randY = rand() % maxInvadersY;

		InitInvader();
		InitBullet();
	}

	void Update() {

		UpdateInvader();
		UpdateBullet();
	}

	void Draw() {

		DrawInvader();
		DrawBullet();
	}

	void DeInit() {

		DeInitInvader();
		DeInitBullet();
	}

	void InitInvader() {

		actualMovement = Horizontal;
		invaderMovementTimer = 0;
		goingRight = true;
		goingLeft = false;
		activeInvaderCounter = maxInvadersX * maxInvadersY;
		maxTimer = 1.0f;

		std::string mainPath = "res/assets/invaders/";

		for (int i = 0; i < maxInvadersY; i++)
		{
			std::string currentInvaderString = FormatText("invader%i", i + 1);
			for (int j = 0; j < maxInvadersX; j++)
			{
				invaders[i][j].body.width = 50;
				invaders[i][j].body.height = 30;
				invaders[i][j].pos.x = ((70 * j)) + invaders[i][j].body.width + 20;
				invaders[i][j].pos.y = static_cast<float>(100 + (60 * i));
				invaders[i][j].body.x = invaders[i][j].pos.x - invaders[i][j].body.width / 2;
				invaders[i][j].body.y = invaders[i][j].pos.y - invaders[i][j].body.height / 2;
				invaders[i][j].speed.x = 20;
				invaders[i][j].speed.y = 30;
				invaders[i][j].active = true;
				invaders[i][j].color = WHITE;
				invaders[i][j].pointsToGive = 100 * i;
			    
				std::string semiCompletePath = mainPath + currentInvaderString + "/" + currentInvaderString;
				std::string currentTextureString;
				std::string fullPath; 
				const char* charPath;

				for (int k = 0; k < maxInvaderAssets; k++)
				{
					currentTextureString = FormatText("_%i.png", k + 1);
					fullPath = semiCompletePath + currentTextureString;
					charPath = fullPath.c_str();
					std::cout << charPath << std::endl;
					invaders[i][j].invaderTexture[k] = LoadTexture(charPath);
				}
				
				for (int k = 0; k < maxBulletAssets; k++)
				{
					currentTextureString = FormatText("_shot%i.png", k + 1);
					fullPath = semiCompletePath + currentTextureString;
					charPath = fullPath.c_str();
					std::cout << charPath << std::endl;
					invaders[i][j].bulletTexture[k] = LoadTexture(charPath);
				}				
			}
		}
	}

	void UpdateInvader() {

		invaderMovementTimer += GetFrameTime();

		if (IsKeyPressed(KEY_K))
		{
			int otherRandX = rand() % maxInvadersX;
			int otherRandY = rand() % maxInvadersY;

			while (!invaders[otherRandY][otherRandX].active)
			{
				otherRandX = rand() % maxInvadersX;
				otherRandY = rand() % maxInvadersY;
			}

			activeInvaderCounter--;
			maxTimer -= 0.01f;
			invaders[otherRandY][otherRandX].active = false;
		}

		for (int i = 0; i < maxInvadersY; i++)
		{
			for (int j = 0; j < maxInvadersX; j++)
			{
				//Body follows the invaderTexture
				invaders[i][j].body.x = invaders[i][j].pos.x - invaders[i][j].body.width / 2;
				invaders[i][j].body.y = invaders[i][j].pos.y - invaders[i][j].body.height / 2;

				//Invader Controls to mimic real movement
				if (IsKeyPressed(KEY_RIGHT))
				{
					invaders[i][j].pos.x += invaders[i][j].speed.x;
				}

				if (IsKeyPressed(KEY_UP))
				{
					invaders[i][j].pos.y -= invaders[i][j].speed.y;
				}

				if (IsKeyPressed(KEY_DOWN))
				{
					invaders[i][j].pos.y += invaders[i][j].speed.y;
				}

				if (IsKeyPressed(KEY_LEFT))
				{
					invaders[i][j].pos.x -= invaders[i][j].speed.x;
				}

				//Real movement
				if (invaderMovementTimer >= maxTimer)
				{
					if (actualMovement == Horizontal)
					{
						for (int k = 0; k < maxInvadersY; k++)
						{
							for (int l = 0; l < maxInvadersX; l++)
							{
								if (invaders[k][l].active)
								{
									invaders[k][l].pos.x += invaders[k][l].speed.x;
								}
							}
						}
					}

					if (actualMovement == Vertical)
					{
						for (int k = 0; k < maxInvadersY; k++)
						{
							for (int l = 0; l < maxInvadersX; l++)
							{
								if (invaders[k][l].active)
								{
									invaders[k][l].pos.y += invaders[k][l].speed.y;
									invaders[k][l].speed.x *= -1;
								}
							}
						}
						actualMovement = Horizontal;
					}

					if (changeMovementTexture) 
					{
						changeMovementTexture = false;
					}
					else
					{
						changeMovementTexture = true;
					}

					invaderMovementTimer = 0;
				}

				if (invaders[i][j].active)
				{
					if ((invaders[i][j].pos.x + invaders[i][j].invaderTexture[0].width / 2 - 10 >= screenWidth) && goingRight)
					{
						goingLeft = true;
						goingRight = false;
						actualMovement = Vertical;
					}

					if ((invaders[i][j].pos.x - invaders[i][j].invaderTexture[0].width / 2 + 10 <= 0) && goingLeft)
					{
						goingRight = true;
						goingLeft = false;
						actualMovement = Vertical;
					}
				}
			}
		}
	}

	void DrawInvader() {

		for (int i = 0; i < maxInvadersY; i++)
		{
			for (int j = 0; j < maxInvadersX; j++)
			{
				if (invaders[i][j].active)
				{
					if (!changeMovementTexture)
					{
						Textures::DrawProTexture(invaders[i][j].invaderTexture[0], invaders[i][j].pos.x, invaders[i][j].pos.y, invaders[i][j].color);
					}
					else
					{
						Textures::DrawProTexture(invaders[i][j].invaderTexture[1], invaders[i][j].pos.x, invaders[i][j].pos.y, invaders[i][j].color);
					}
				}
			}
		}
	}

	void InitBullet() {

		bulletTimer = 0;

		bullet.rec.width = 45;
		bullet.rec.height = 50;
		bullet.pos.x = invaders[randY][randX].pos.x;
		bullet.pos.y = invaders[randY][randX].pos.y + 20;
		bullet.rec.x = bullet.rec.x - bullet.rec.width / 2;
		bullet.rec.y = bullet.rec.y - bullet.rec.height / 2;
		bullet.speed = 200.0f;
		bullet.active = true;
		bullet.color = WHITE;
	}

	void UpdateBullet() {

		bulletTimer += GetFrameTime();

		if (bulletTimer >= 0.4)
		{
			bulletTimer = 0;
		}

		bullet.rec.x = bullet.pos.x - bullet.rec.width / 2;
		bullet.rec.y = bullet.pos.y - bullet.rec.height / 2;

		if (bullet.active)
		{
			for (int i = 0; i < maxBulletAssets; i++)
			{
				bullet.texture[i] = invaders[randY][randX].bulletTexture[i];

				if (bullet.pos.y - bullet.texture[i].height / 2 > screenHeight)
				{
					bulletRespawn();
				}
			}

			bullet.pos.y += bullet.speed * GetFrameTime();
		}
		else
		{
			bulletRespawn();
		}
	}

	void bulletRespawn() {

		if (activeInvaderCounter != 0)
		{
			randX = rand() % maxInvadersX;
			randY = rand() % maxInvadersY;

			while (!invaders[randY][randX].active)
			{
				randX = rand() % maxInvadersX;
				randY = rand() % maxInvadersY;
			}

			bullet.pos.x = invaders[randY][randX].pos.x;
			bullet.pos.y = invaders[randY][randX].pos.y;

			bullet.active = true;
		}
	}

	void DrawBullet() {

		if (bullet.active)
		{
			if (bulletTimer < 0.1f)
			{
				Textures::DrawProTexture(bullet.texture[0], bullet.pos.x, bullet.pos.y, bullet.color);
			}

			if (bulletTimer > 0.1f && bulletTimer < 0.2f)
			{
				Textures::DrawProTexture(bullet.texture[1], bullet.pos.x, bullet.pos.y, bullet.color);
			}

			if (bulletTimer > 0.2f && bulletTimer < 0.3f)
			{
				Textures::DrawProTexture(bullet.texture[2], bullet.pos.x, bullet.pos.y, bullet.color);
			}

			if (bulletTimer > 0.3f && bulletTimer < 0.4f)
			{
				Textures::DrawProTexture(bullet.texture[3], bullet.pos.x, bullet.pos.y, bullet.color);
			}

			//DrawRectangleRec(bullet.rec, bullet.color);
		}
	}

	void DeInitInvader() {

		for (int i = 0; i < maxInvadersY; i++)
		{
			for (int j = 0; j < maxInvadersX; j++)
			{
				UnloadTexture(invaders[i][j].invaderTexture[0]);
				UnloadTexture(invaders[i][j].invaderTexture[1]);

				for (int k = 0; k < maxBulletAssets; k++)
				{
					UnloadTexture(invaders[i][j].bulletTexture[k]);
				}
			}
		}
	}

	void DeInitBullet() {

		for (int i = 0; i < maxBulletAssets; i++)
		{
			UnloadTexture(bullet.texture[i]);
		}
	}
}
}