#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

namespace MyGame {
namespace MenuManager{

	enum MenuScene {
		LevelSelection,
		Options,
		Controls,
		Credits,
	};

	extern MenuScene actualMenuScene;

	extern bool optionsActive;
	extern bool controlsActive;
	extern bool CreditsActive;

	void init();
	void update();
	void draw();
	void deInit();
}
}

#endif