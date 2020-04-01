#include "invaders.h"

#include <iostream>
#include <time.h>

#include "game_manager.h"

namespace MyGame{
namespace Invaders{
using namespace GameManager;
	
	static void initInvader();
	static void updateInvader();
	static void drawInvader();
	static void initBullet();
	static void updateBullet();
	static void bulletRespawn();
	static void drawBullet();

	static void deInitInvader();
	static void deInitBullet();

	enum InvaderMovement {
		Horizontal,
		Vertical,
	};

	static InvaderMovement actualMovement = Horizontal;

	Bullet bullet;

	Invader invaders[maxInvadersY][maxInvadersX];

	static int randX;
	static int randY;

	static bool goingRight = true;
	static bool goingLeft = false;
	static int movementCounter;
	static float invaderMovementTimer;
	static float invaderTextureTimer;
	static float bulletTimer;

	int activeInvaderCounter = maxInvadersX * maxInvadersY;
	float maxTimer = 1.0f;
	
	void init(){
		
		srand(time(0));
		randX = rand() % maxInvadersX;
		randY = rand() % maxInvadersY;

		initInvader();
		initBullet();
	}

	void update() {

		updateInvader();
		updateBullet();
	}

	void draw() {

		drawInvader();
		drawBullet();
	}

	void deInit() {

		deInitInvader();
		deInitBullet();
	}

	void initInvader() {

		invaderMovementTimer = 0;
		invaderTextureTimer = 0;
		movementCounter = 0;

		for (int i = 0; i < maxInvadersY; i++)
		{
			for (int j = 0; j < maxInvadersX; j++)
			{
				invaders[i][j].body.width = 40;
				invaders[i][j].body.height = 30;
				invaders[i][j].pos.x = ((70 * j)) + invaders[i][j].body.width + 20;
				invaders[i][j].pos.y = 70 + (60 * i);
				invaders[i][j].body.x = invaders[i][j].pos.x - invaders[i][j].body.width / 2;
				invaders[i][j].body.y = invaders[i][j].pos.y - invaders[i][j].body.height / 2;
				invaders[i][j].speed.x = 20;
				invaders[i][j].speed.y = 20;
				invaders[i][j].active = true;
				invaders[i][j].color = WHITE;

				switch (i)
				{
				case 0:
					invaders[i][j].pointsToGive = 300;
					invaders[i][j].invaderTexture[0] = LoadTexture("res/textures/invaders/invader3/invader3_1.png");
					invaders[i][j].invaderTexture[1] = LoadTexture("res/textures/invaders/invader3/invader3_2.png");
					invaders[i][j].bulletTexture[0] = LoadTexture("res/textures/invaders/invader3/invader3_shot1.png");
					invaders[i][j].bulletTexture[1] = LoadTexture("res/textures/invaders/invader3/invader3_shot2.png");
					invaders[i][j].bulletTexture[2] = LoadTexture("res/textures/invaders/invader3/invader3_shot3.png");
					invaders[i][j].bulletTexture[3] = LoadTexture("res/textures/invaders/invader3/invader3_shot4.png");
					break;

				case 1:
				case 2:
					invaders[i][j].pointsToGive = 200;
					invaders[i][j].invaderTexture[0] = LoadTexture("res/textures/invaders/invader2/invader2_1.png");
					invaders[i][j].invaderTexture[1] = LoadTexture("res/textures/invaders/invader2/invader2_2.png");
					invaders[i][j].bulletTexture[0] = LoadTexture("res/textures/invaders/invader2/invader2_shot1.png");
					invaders[i][j].bulletTexture[1] = LoadTexture("res/textures/invaders/invader2/invader2_shot2.png");
					invaders[i][j].bulletTexture[2] = LoadTexture("res/textures/invaders/invader2/invader2_shot3.png");
					invaders[i][j].bulletTexture[3] = LoadTexture("res/textures/invaders/invader2/invader2_shot4.png");
					break;

				case 3:
				case 4:
					invaders[i][j].pointsToGive = 100;
					invaders[i][j].invaderTexture[0] = LoadTexture("res/textures/invaders/invader1/invader1_1.png");
					invaders[i][j].invaderTexture[1] = LoadTexture("res/textures/invaders/invader1/invader1_2.png");
					invaders[i][j].bulletTexture[0] = LoadTexture("res/textures/invaders/invader1/invader1_shot1.png");
					invaders[i][j].bulletTexture[1] = LoadTexture("res/textures/invaders/invader1/invader1_shot2.png");
					invaders[i][j].bulletTexture[2] = LoadTexture("res/textures/invaders/invader1/invader1_shot3.png");
					invaders[i][j].bulletTexture[3] = LoadTexture("res/textures/invaders/invader1/invader1_shot4.png");
					break;

				default:
					break;
				}
			}
		}
	}

	void updateInvader() {

		invaderTextureTimer += GetFrameTime();
		invaderMovementTimer += GetFrameTime();

		if (invaderTextureTimer >= maxTimer * 2)
		{
			invaderTextureTimer = 0;
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

				if (actualMovement == Horizontal)
				{
					if (invaderMovementTimer >= maxTimer)
					{
						for (int k = 0; k < maxInvadersY; k++)
						{
							for (int l = 0; l < maxInvadersX; l++)
							{
								invaders[k][l].pos.x += invaders[k][l].speed.x;
								invaderMovementTimer = 0;
							}
						}
					}

					if (invaders[i][j].active)
					{
						if (invaders[i][j].pos.x + invaders[i][j].invaderTexture[0].width / 2 - 10 >= screenWidth && goingRight)
						{
							goingLeft = true;
							goingRight = false;
							actualMovement = Vertical;
						}

						if (invaders[i][j].pos.x - invaders[i][j].invaderTexture[0].width / 2 + 10 <= 0 && goingLeft)
						{
							goingRight = true;
							goingLeft = false;
							actualMovement = Vertical;
						}
					}
				}

				if (actualMovement == Vertical)
				{
					if (invaderMovementTimer >= maxTimer)
					{
						for (int k = 0; k < maxInvadersY; k++)
						{
							for (int l = 0; l < maxInvadersX; l++)
							{
								invaders[k][l].pos.y += invaders[k][l].speed.y;
								invaders[k][l].speed.x *= -1;
								invaderMovementTimer = 0;
							}
						}
						actualMovement = Horizontal;
					}
				}
			}
		}
	}

	void drawInvader() {

		for (int i = 0; i < maxInvadersY; i++)
		{
			for (int j = 0; j < maxInvadersX; j++)
			{
				//DrawRectangleRec(invaders[i][j].body, invaders[i][j].color);
				if (invaders[i][j].active)
				{
					if (invaderTextureTimer <= maxTimer)
					{
						DrawTexture(invaders[i][j].invaderTexture[0], invaders[i][j].pos.x - invaders[i][j].invaderTexture[0].width / 2, invaders[i][j].pos.y - invaders[i][j].invaderTexture[0].height / 2, invaders[i][j].color);
					}
					else
					{
						DrawTexture(invaders[i][j].invaderTexture[1], invaders[i][j].pos.x - invaders[i][j].invaderTexture[1].width / 2, invaders[i][j].pos.y - invaders[i][j].invaderTexture[1].height / 2, invaders[i][j].color);
					}
				}
			}
		}
	}

	void initBullet() {

		bulletTimer = 0;

		bullet.rec.width = 55;
		bullet.rec.height = 55;
		bullet.pos.x = invaders[randY][randX].pos.x;
		bullet.pos.y = invaders[randY][randX].pos.y + 20;
		bullet.rec.x = bullet.rec.x - bullet.rec.width / 2;
		bullet.rec.y = bullet.rec.y - bullet.rec.height / 2;
		bullet.speed = 200.0f;
		bullet.active = true;
		bullet.color = RED;
	}

	void updateBullet() {

		bulletTimer += GetFrameTime();

		if (bulletTimer >= 0.4)
		{
			bulletTimer = 0;
		}

		bullet.rec.x = bullet.pos.x - bullet.rec.width / 2;
		bullet.rec.y = bullet.pos.y - bullet.rec.height / 2;

		if (bullet.active)
		{
			for (int i = 0; i < maxBulletTextures; i++)
			{
				bullet.textures[i] = invaders[randY][randX].bulletTexture[i];

				if (bullet.pos.y - bullet.textures[i].height / 2 > screenHeight)
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

	void drawBullet() {

		if (bullet.active)
		{
			if (bulletTimer < 0.1f)
			{
				DrawTexture(bullet.textures[0], bullet.pos.x - bullet.textures[0].width / 2, bullet.pos.y - bullet.textures[0].height / 2, WHITE);
			}

			if (bulletTimer > 0.1f && bulletTimer < 0.2f)
			{
				DrawTexture(bullet.textures[1], bullet.pos.x - bullet.textures[1].width / 2, bullet.pos.y - bullet.textures[1].height / 2, WHITE);
			}

			if (bulletTimer > 0.2f && bulletTimer < 0.3f)
			{
				DrawTexture(bullet.textures[2], bullet.pos.x - bullet.textures[2].width / 2, bullet.pos.y - bullet.textures[2].height / 2, WHITE);
			}

			if (bulletTimer > 0.3f && bulletTimer < 0.4f)
			{
				DrawTexture(bullet.textures[3], bullet.pos.x - bullet.textures[3].width / 2, bullet.pos.y - bullet.textures[3].height / 2, WHITE);
			}

			//DrawRectangleRec(bullet.rec, bullet.color);
		}
	}

	void deInitInvader() {

		for (int i = 0; i < maxInvadersY; i++)
		{
			for (int j = 0; j < maxInvadersX; j++)
			{
				UnloadTexture(invaders[i][j].invaderTexture[0]);
				UnloadTexture(invaders[i][j].invaderTexture[1]);

				for (int k = 0; k < maxBulletTextures; k++)
				{
					UnloadTexture(invaders[i][j].bulletTexture[k]);
				}
			}
		}
	}

	void deInitBullet() {

		for (int i = 0; i < maxBulletTextures; i++)
		{
			UnloadTexture(bullet.textures[i]);
		}
	}
}
}