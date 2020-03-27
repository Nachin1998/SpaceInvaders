#include "player.h"

#include "game_manager.h"

namespace MyGame {
namespace Player {
using namespace GameManager;

	static void updatePlayer();
	static void drawPlayer();
	static void updateBullet();
	static void drawBullet();
	
	Bullet bullet;

	Player player;

	static float textureTimer;
	static float maxTextureTimer = 0.4f;

	static int mapLimit = 10;

	void init() {

		textureTimer = 0;

		player.pos.x = screenWidth / 2;
		player.pos.y = screenHeight / 2 + 420;
		player.body.width = 80;
		player.body.height = 80;
		player.body.x = player.pos.x - player.body.width / 2;
		player.body.y = player.pos.y - player.body.height / 2;
		player.speed.x = 250;
		player.speed.y = 250;
		player.points = 0;
		player.lives = 3;
		player.texture[0] = LoadTexture("res/textures/player/player_spaceship1.png");
		player.texture[1] = LoadTexture("res/textures/player/player_spaceship2.png");
		player.texture[2] = LoadTexture("res/textures/player/player_spaceship3.png");
		player.texture[3] = LoadTexture("res/textures/player/player_spaceship4.png");
		player.color = WHITE;

		bullet.rec.width = 5;
		bullet.rec.height = 15;
		bullet.rec.x = player.pos.x - bullet.rec.width / 2;
		bullet.rec.y = player.pos.y - bullet.rec.height / 2;
		bullet.speed = 1200.0f;
		bullet.active = false;
		bullet.color = RED;
	}

	void update() {
		textureTimer += GetFrameTime();

		if (textureTimer >= maxTextureTimer)
		{
			textureTimer = 0;
		}

		player.body.x = player.pos.x - player.body.width / 2;
		player.body.y = player.pos.y - player.body.height / 2;

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
	}

	void updatePlayer() {

		if (IsKeyDown(KEY_W))
		{
			player.pos.y -= player.speed.x * GetFrameTime();
		}

		if (IsKeyDown(KEY_S))
		{
			player.pos.y += player.speed.x * GetFrameTime();
		}

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
	}

	void drawPlayer() {

		//DrawRectangleRec(player.body, player.color);

		if (textureTimer < 0.1f)
		{
			DrawTexture(player.texture[0], player.pos.x - player.texture[0].width / 2, player.pos.y - player.texture[0].height / 2, player.color);
		}

		if (textureTimer > 0.1f && textureTimer < 0.2f)
		{
			DrawTexture(player.texture[1], player.pos.x - player.texture[1].width / 2, player.pos.y - player.texture[1].height / 2, player.color);
		}

		if (textureTimer > 0.2f && textureTimer < 0.3f)
		{
			DrawTexture(player.texture[2], player.pos.x - player.texture[2].width / 2, player.pos.y - player.texture[2].height / 2, player.color);
		}

		if (textureTimer > 0.3f && textureTimer < maxTextureTimer)
		{
			DrawTexture(player.texture[3], player.pos.x - player.texture[3].width / 2, player.pos.y - player.texture[3].height / 2, player.color);
		}
	}

	void updateBullet() {

		if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			bullet.active = true;
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