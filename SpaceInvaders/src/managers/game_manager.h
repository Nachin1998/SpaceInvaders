#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "raylib.h"

namespace MyGame {
namespace GameManager {

	const int screenWidth = 900;
	const int screenHeight = 1000;

	enum SpaceInvadersScenes {
		MainMenu,
		Gameplay,
		GameOver
	};

	extern SpaceInvadersScenes actualScene;
	extern Music backgroundMusic;
	extern bool endGame;
	void runGame();
}
}

#endif
