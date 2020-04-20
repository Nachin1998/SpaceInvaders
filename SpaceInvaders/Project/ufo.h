#ifndef UFO_H
#define UFO_H

#include "raylib.h"

namespace MyGame {
namespace Ufo {
	
	const int ufoMaxTextures = 2;

	struct UFO {
		Rectangle rec;
		Texture2D texture[ufoMaxTextures];
		Vector2 pos;
		float speed;
		int pointsToGive;
		bool active;
		bool attacking;
		Color color;
	};
	
	extern UFO ufo;
	extern float ufoMovementTimer;
	extern float ufoTextureTimer;

	void init();
	void update();
	void draw();
	void deInit();
}
}

#endif