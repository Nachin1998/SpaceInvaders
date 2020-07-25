#include "menu_manager.h"

#include "raylib.h"

#include "scenes\gameplay.h"

#include "scenes\main_menu.h"
#include "scenes\options.h"
#include "scenes\controls.h"
#include "scenes\credits.h"

namespace MyGame {
	namespace MenuManager {

		MenuScene actualMenuScene = Menu;

		static Texture2D background;

		bool creditsActive = false;

		void init() {

			background = LoadTexture("res/assets/background/main_menu/main_menu_background.png");

			MainMenu::init();
			Options::init();
			Controls::init();
			Credits::init();
		}

		void update() {

			if (!creditsActive)
			{
				MainMenu::update();
			}

			switch (actualMenuScene)
			{
			case Menu:
				break;

			case Options:
				Options::update();
				break;

			case Controls:
				Controls::update();
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

			if (!creditsActive)
			{
				MainMenu::draw();
			}

			switch (actualMenuScene)
			{
			case Menu:
				break;

			case Options:
				Options::draw();
				break;

			case Controls:
				Controls::draw();
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