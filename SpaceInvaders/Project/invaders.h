#ifndef INVADERS_H
#define INVADERS_H

#include "raylib.h"

namespace MyGame {
namespace Invaders {
	
	const int maxInvaderTextures = 2;
	const int maxBulletTextures = 4;
	const int maxInvadersX = 11;
	const int maxInvadersY = 5;

	struct Invader {
		Rectangle body;
		Texture2D invaderTexture[maxInvaderTextures];
		Texture2D bulletTexture[maxBulletTextures];
		Vector2 pos;
		Vector2 speed;
		bool active;
		Color color;
	};

	struct Bullet {
		Texture2D textures[maxBulletTextures];
		Vector2 pos;
		Rectangle rec;
		float speed;
		bool active;
		Color color;
	};

	extern Invader invaders[maxInvadersY][maxInvadersX];
	extern Bullet bullet;

	extern int activeInvaderCounter;

	void init();
	void update();
	void draw();
	void deInit();
	void bulletRespawn();
}
}

#endif
