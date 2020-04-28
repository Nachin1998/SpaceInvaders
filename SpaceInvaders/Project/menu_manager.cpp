#include "menu_manager.h"

#include "gameplay.h"

#include "main_menu.h"
#include "controls.h"

namespace MyGame {
namespace MenuManager{

	MenuScene actualMenuScene = LevelSelection;

	bool optionsActive = false;
	bool controlsActive = false;
	bool CreditsActive = false;

	void init() {

		MainMenu::init();
		Controls::init();
		Gameplay::init();
	}

	void update() {

		MainMenu::update();

		switch (actualMenuScene)
		{
		case LevelSelection:
			break;

		case Options:
			break;

		case Controls:
			if (controlsActive)
			{
				Controls::update();
			}
			break;

		case Credits:
			Gameplay::update();
			break;

		default:
			break;
		}
	}

	void draw() {

		MainMenu::draw();

		switch (actualMenuScene)
		{
		case LevelSelection:
			break;

		case Options:
			break;

		case Controls:
			if (controlsActive)
			{
				Controls::draw();
			}
			break;

		case Credits:
			Gameplay::draw();
			break;

		default:
			break;
		}
	}

	void deInit() {

		MainMenu::deInit();
	}
}
}