#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

namespace MyGame {
namespace MenuManager{

	enum MenuScene {
		Menu,
		Controls,
		Credits,
	};

	extern MenuScene actualMenuScene;

	extern bool mainMenuActive;
	extern bool controlsActive;
	extern bool creditsActive;

	void init();
	void update();
	void draw();
	void deInit();
}
}

#endif