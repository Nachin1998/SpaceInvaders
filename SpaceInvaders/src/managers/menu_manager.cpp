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

		void Init() {

			background = LoadTexture("res/assets/background/main_menu/main_menu_background.png");

			MainMenu::Init();
			Options::Init();
			Controls::Init();
			Credits::Init();
		}

		void Update() {

			if (!creditsActive)
			{
				MainMenu::Update();
			}

			switch (actualMenuScene)
			{
			case Menu:
				break;

			case Options:
				Options::Update();
				break;

			case Controls:
				Controls::Update();
				break;

			case Credits:
				if (creditsActive)
				{
					Credits::Update();
				}
				break;

			default:
				break;
			}
		}

		void Draw() {

			DrawTexture(background, 0, 0, WHITE);

			if (!creditsActive)
			{
				MainMenu::Draw();
			}

			switch (actualMenuScene)
			{
			case Menu:
				break;

			case Options:
				Options::Draw();
				break;

			case Controls:
				Controls::Draw();
				break;

			case Credits:
				if (creditsActive)
				{
					Credits::Draw();
				}
				break;

			default:
				break;
			}
		}

		void DeInit() {

			UnloadTexture(background);
		}
	}
}