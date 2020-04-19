#ifndef INVADERS_H
#define INVADERS_H

#include "raylib.h"

namespace MyGame {
namespace Invaders {
	
	const int maxInvaderassets = 2;
	const int maxBulletassets = 4;
	const int maxInvadersX = 11;
	const int maxInvadersY = 5;

	struct Invader {
		Rectangle body;
		Texture2D invaderTexture[maxInvaderassets];
		Texture2D bulletTexture[maxBulletassets];
		Vector2 pos;
		Vector2 speed;
		int pointsToGive;
		bool active;
		Color color;
	};

	struct Bullet {
		Texture2D assets[maxBulletassets];
		Vector2 pos;
		Rectangle rec;
		float speed;
		bool active;
		Color color;
	};

	extern Invader invaders[maxInvadersY][maxInvadersX];
	extern Bullet bullet;

	extern float maxTimer;
	extern int activeInvaderCounter;

	void init();
	void update();
	void draw();
	void deInit();
}
}

#endif
