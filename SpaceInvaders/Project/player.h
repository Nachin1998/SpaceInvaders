#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

namespace MyGame {
	namespace Player {

		struct Player {
			Rectangle rec;
			Texture2D texture;
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
