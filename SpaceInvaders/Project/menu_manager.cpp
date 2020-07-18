#include "menu_manager.h"

#include "raylib.h"

#include "gameplay.h"

#include "main_menu.h"
#include "controls.h"
#include "credits.h"

namespace MyGame {
namespace MenuManager{

	MenuScene actualMenuScene = Menu;

	static Texture2D background;

	bool mainMenuActive = true;
	bool controlsActive = false;
	bool creditsActive = false;

	void init() {

		background = LoadTexture("res/assets/background/main_menu/main_menu_background.png");

		MainMenu::init();
		Controls::init();
		Credits::init();
	}

	void update() {

		if (mainMenuActive)
		{
			MainMenu::update();
		}

		switch (actualMenuScene)
		{
		case Menu:
			break;

		case Controls:
			if (controlsActive)
			{
				Controls::update();
			}
			break;

		case Credits:
			if (creditsActive)
			{
				Credits::update();
			}
			break;

		default:
			break;
		}
	}

	void draw() {

		DrawTexture(background, 0, 0, WHITE);

		if (mainMenuActive) 
		{
			MainMenu::draw();
		}

		switch (actualMenuScene)
		{
		case Menu:
			break;

		case Controls:
			if (controlsActive)
			{
				Controls::draw();
			}
			break;

		case Credits:
			if (creditsActive)
			{
				Credits::draw();
			}
			break;

		default:
			break;
		}
	}

	void deInit() {

		UnloadTexture(background);
	}
}
}