#include "player.h"

#include "managers\game_manager.h"
#include "utility\utility.h"

namespace MyGame {
namespace Player {
using namespace GameManager;

	static void updatePlayer();
	static void drawPlayer();
	static void updateBullet();
	static void drawBullet();
	
	Bullet bullet;

	Player player;

	static Sound laserShot;

	static float textureTimer;
	static float maxTextureTimer = 0.4f;

	static int mapLimit = 10;
	static Color healthColor;
	void init() {

		textureTimer = 0;

		player.pos.x = screenWidth / 2;
		player.pos.y = screenHeight / 2 + 420;
		player.body.width = 80;
		player.body.height = 80;
		player.body.x = player.pos.x - player.body.width / 2;
		player.body.y = player.pos.y - player.body.height / 2;		
		player.healthRec.width = screenWidth;
		player.healthRec.height = screenHeight;
		player.healthRec.x = screenWidth / 2 - player.healthRec.width / 2;
		player.healthRec.y = screenHeight / 2 - player.healthRec.height / 2;
		player.speed.x = 250;
		player.speed.y = 250;
		player.points = 0;
		player.lives = 3;
		player.isDead = false;
		player.texture[0] = LoadTexture("res/assets/player/player_spaceship1.png");
		player.texture[1] = LoadTexture("res/assets/player/player_spaceship2.png");
		player.texture[2] = LoadTexture("res/assets/player/player_spaceship3.png");
		player.texture[3] = LoadTexture("res/assets/player/player_spaceship4.png");
		player.color = WHITE;

		bullet.rec.width = 5;
		bullet.rec.height = 15;
		bullet.rec.x = player.pos.x - bullet.rec.width / 2;
		bullet.rec.y = player.pos.y - bullet.rec.height / 2;
		bullet.speed = 700.0f;
		bullet.active = false;
		bullet.color = RED;

		laserShot = LoadSound("res/sounds/LaserShot.ogg");
		SetSoundVolume(laserShot, 0.3f);
	}

	void update() {

		textureTimer += GetFrameTime();
		if (textureTimer >= maxTextureTimer)
		{
			textureTimer = 0;
		}

		updatePlayer();
		updateBullet();
	}
	
	void draw() {

		drawBullet();
		drawPlayer();
	}

	void deInit() {

		for (int i = 0; i < maxTextures; i++)
		{
			UnloadTexture(player.texture[i]);
		}
		UnloadSound(laserShot);
	}

	void updatePlayer() {

		player.body.x = player.pos.x - player.body.width / 2;
		player.body.y = player.pos.y - player.body.height / 2;

		if(player.body.x - mapLimit > 0)
		{
			if (IsKeyDown(KEY_A))
			{
				player.pos.x -= player.speed.y * GetFrameTime();
			}
		}
		
		if (player.body.x +player.body.width + mapLimit < screenWidth)
		{
			if (IsKeyDown(KEY_D))
			{
				player.pos.x += player.speed.y * GetFrameTime();
			}
		}

		if (player.lives <= 0) 
		{
			player.isDead = true;
		}

		switch (player.lives)
		{
		case 3:
			healthColor = GREEN;
			break;
		case 2:
			healthColor = YELLOW;
			break;
		case 1:
			healthColor = RED;
			break;

		default:
			healthColor = BLACK;
			break;
		}
	}

	void drawPlayer() {
		
		if (textureTimer < 0.1f)
		{
			Textures::drawProTexture(player.texture[0], player.pos.x, player.pos.y, player.color);
		}

		if (textureTimer > 0.1f && textureTimer < 0.2f)
		{
			Textures::drawProTexture(player.texture[1], player.pos.x, player.pos.y, player.color);
		}

		if (textureTimer > 0.2f && textureTimer < 0.3f)
		{
			Textures::drawProTexture(player.texture[2], player.pos.x, player.pos.y, player.color);
		}

		if (textureTimer > 0.3f && textureTimer < maxTextureTimer)
		{
			Textures::drawProTexture(player.texture[3], player.pos.x, player.pos.y, player.color);
		}

		DrawRectangleLinesEx(player.healthRec, 5, healthColor);
	}

	void updateBullet() {

		if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			if (!bullet.active) 
			{
				PlaySound(laserShot);
				bullet.active = true;
			}			
		}

		if (bullet.active)
		{
			bullet.rec.y -= bullet.speed * GetFrameTime();
		}
		else
		{
			bullet.rec.x = player.pos.x - bullet.rec.width / 2;
			bullet.rec.y = player.pos.y - player.body.height / 2 - bullet.rec.height / 2;
		}

		if (bullet.rec.y < 0)
		{
			bullet.active = false;
		}
	}
	
	void drawBullet() {

		if (bullet.active)
		{
			DrawRectangleRec(bullet.rec, bullet.color);
		}
	}
}
}