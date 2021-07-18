#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

namespace MyGame {
namespace Player {

	const int maxTextures = 4;

	struct Player {
		Rectangle body;
		Rectangle healthRec;
		Texture2D texture[maxTextures];
		Vector2 pos;
		Vector2 speed;
		int points;
		int lives;
		bool isDead;
		Color color;
	};

	struct Bullet {
		Rectangle rec;
		float speed;
		bool active;
		Color color;
	};

	extern Player player;
	extern Bullet bullet;

	void Init();
	void Update();
	void Draw();
	void DeInit();
}
}

#endif
