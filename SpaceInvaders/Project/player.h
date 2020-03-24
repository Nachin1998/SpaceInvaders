#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

namespace MyGame {
namespace Player {

	const int maxTextures = 4;

	struct Player {
		Rectangle body;
		Texture2D texture[maxTextures];
		Vector2 pos;
		Vector2 speed;
		int lives;
		Color color;
	};

	extern Player player;

	void init();
	void update();
	void draw();
	void deInit();
}
}

#endif
