#include "player.h"

#include "game_manager.h"

namespace MyGame {
namespace Player {
using namespace GameManager;

	static void playerMovement();

	float maxTextureTimer = 0.4f;
	Player player;
	float textureTimer;

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
		player.lives = 3;
		player.texture[0] = LoadTexture("res/player/player_spaceship1.png");
		player.texture[1] = LoadTexture("res/player/player_spaceship2.png");
		player.texture[2] = LoadTexture("res/player/player_spaceship3.png");
		player.texture[3] = LoadTexture("res/player/player_spaceship4.png");
		player.color = WHITE;
	}

	void update() {
		textureTimer += GetFrameTime();

		if (textureTimer >= maxTextureTimer)
		{
			textureTimer = 0;
		}

		player.body.x = player.pos.x - player.body.width / 2;
		player.body.y = player.pos.y - player.body.height / 2;

		playerMovement();
	}
	
	void draw() {

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

	void deInit() {

		for (int i = 0; i < maxTextures; i++)
		{
			UnloadTexture(player.texture[i]);
		}
	}

	void playerMovement() {

		if(player.body.x - 10 > 0)
		{
			if (IsKeyDown(KEY_A))
			{
				player.pos.x -= player.speed.y * GetFrameTime();
			}
		}
		
		if (player.body.x +player.body.width + 10 < screenWidth)
		{
			if (IsKeyDown(KEY_D))
			{
				player.pos.x += player.speed.y * GetFrameTime();
			}
		}
	}
}
}