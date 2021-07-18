#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

namespace MyGame {
namespace MenuManager{

	enum MenuScene {
		Menu,
		Options, 
		Controls,
		Credits,
	};

	extern MenuScene actualMenuScene;

	extern bool creditsActive;

	void Init();
	void Update();
	void Draw();
	void DeInit();
}
}

#endif