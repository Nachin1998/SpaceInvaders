#ifndef INVADERS_H
#define INVADERS_H

#include "raylib.h"

namespace MyGame {
namespace Invaders {
	
	const int maxInvaderAssets = 2;
	const int maxBulletAssets = 4;
	const int maxInvadersX = 11;
	const int maxInvadersY = 5;

	struct Invader {
		Rectangle body;
		Texture2D invaderTexture[maxInvaderAssets];
		Texture2D bulletTexture[maxBulletAssets];
		Vector2 pos;
		Vector2 speed;
		int pointsToGive;
		bool active;
		Color color;
	};

	struct Bullet {
		Texture2D texture[maxBulletAssets];
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

	void Init();
	void Update();
	void Draw();
	void DeInit();
}
}

#endif
