#include "main_menu.h"

#include "menu_manager.h"
#include "game_manager.h"

#include "utility.h"

namespace MyGame {
namespace MainMenu {
using namespace GameManager;
using namespace UI;

	static const int maxButtons = 5;

	UI::Button title;
	UI::Button menuButton[maxButtons];

	static Texture2D background;

	void init() {

		title.rec.width = 700;
		title.rec.height = 100;
		title.rec.x = screenWidth / 2 - title.rec.width / 2;
		title.rec.y = 100 - title.rec.height / 2;
		initButton(title, title.rec, 3, 70, GREEN, DARKGRAY);

		for (int i = 0; i < maxButtons; i++)
		{
			menuButton[i].rec.width = 250;
			menuButton[i].rec.height = 70;
			menuButton[i].rec.x = 170 - menuButton[i].rec.width / 2;;
			menuButton[i].rec.y = screenHeight / 2 - 100 + (120 * i) - menuButton[i].rec.height / 2;
			initButton(menuButton[i], menuButton[i].rec, 3, 50, BLANK, GREEN);
		}

		background = LoadTexture("res/assets/background/main_menu/main_menu_background.png");
	}

	void update() {

		Vector2 mousePos = GetMousePosition();

		for (int i = 0; i < maxButtons; i++)
		{
			updateButton(menuButton[i], BLANK, DARKGRAY);

			if (CheckCollisionPointRec(mousePos, menuButton[i].rec))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					switch (i)
					{
					case 0:
						MenuManager::actualMenuScene = MenuManager::LevelSelection;
						actualScene = Gameplay;
						break;

					case 1:
						break;

					case 2:
						if (MenuManager::controlsActive)
						{
							MenuManager::controlsActive = false;
						}
						else
						{
							MenuManager::controlsActive = true;
						}
						MenuManager::actualMenuScene = MenuManager::Controls;
						break;

					case 3:
						break;

					case 4:
						endGame = true;
						break;

					default:
						break;
					}
				}
			}
		}		
	}

	void draw() {

		DrawTexture(background, 0, 0, WHITE);

		drawButton("Space Conquerors", title);
		drawButton("Start", menuButton[0]);
		drawButton("Options", menuButton[1]);
		drawButton("Controls", menuButton[2]);
		drawButton("Credits", menuButton[3]);
		drawButton("Exit", menuButton[4]);
	}

	void deInit() {

		UnloadTexture(background);
	}
}
}