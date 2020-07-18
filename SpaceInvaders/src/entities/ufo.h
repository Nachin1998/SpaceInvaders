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
	
	const int maxSounds = 3;

	extern UFO ufo;
	extern Laser laser;
	extern Sound sounds[maxSounds];
	extern float ufoActivationTimer;
	extern float timeUntillActive;

	void init();
	void update();
	void draw();
	void deInit();
}
}

#endif