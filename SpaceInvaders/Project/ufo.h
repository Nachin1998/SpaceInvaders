#ifndef UFO_H
#define UFO_H

#include "raylib.h"

namespace MyGame {
namespace Ufo {
	
	const int ufoMaxTextures = 6;

	struct UFO {
		Rectangle rec;
		Texture2D idleTexture[ufoMaxTextures];
		Texture2D chargingTexture[ufoMaxTextures];
		Texture2D attackingTexture[ufoMaxTextures];
		Vector2 pos;
		float speed;
		int pointsToGive;
		bool active;
		Color color;
	};

	struct Laser {
		Rectangle rec;
		Vector2 pos;
		Texture2D texture;
		bool active;
		Color color;
	};
	
	extern UFO ufo;
	extern Laser laser;
	extern float ufoActivationTimer;

	void init();
	void update();
	void draw();
	void deInit();
}
}

#endif