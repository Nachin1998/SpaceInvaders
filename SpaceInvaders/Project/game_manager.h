#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

namespace MyGame {
namespace GameManager {

	const int screenWidth = 900;
	const int screenHeight = 1000;

	enum SpaceInvadersScenes {
		MainMenu,
		Gameplay,
		GameOver,
		Credits
	};

	extern SpaceInvadersScenes actualScene;

	extern bool endGame;
	void runGame();
}
}

#endif
