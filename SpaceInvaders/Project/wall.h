#ifndef WALL_H
#define WALL_H

#include "raylib.h"

namespace MyGame {
namespace Wall {

	const int maxWalls = 4;
	const int maxWallsTextures = 2;

	struct Wall {
		Rectangle rec;
		Texture2D texture[maxWallsTextures];
		int lives;
		Vector2 pos;
		bool active;
		Color color;
	};
	extern Wall walls[maxWalls];

	void init();
	void update();
	void draw();
	void deInit();
}
}

#endif
