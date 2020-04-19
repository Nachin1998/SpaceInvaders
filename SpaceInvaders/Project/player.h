#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

namespace MyGame {
namespace Player {

	const int maxassets = 4;

	struct Player {
		Rectangle body;
		Texture2D texture[maxassets];
		Vector2 pos;
		Vector2 speed;
		int points;
		int lives;
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

	void init();
	void update();
	void draw();
	void deInit();
}
}

#endif
