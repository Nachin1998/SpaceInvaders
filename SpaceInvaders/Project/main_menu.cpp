#include "main_menu.h"

#include "menu_manager.h"
#include "game_manager.h"
#include "gameplay.h"
#include "utility.h"

namespace MyGame {
namespace MainMenu {
using namespace GameManager;
using namespace UI;

	static const int maxButtons = 4;

	static Button title;
	static Button menuButton[maxButtons];

	void init() {

		title.rec.width = 800;
		title.rec.height = 100;
		title.rec.x = screenWidth / 2 - title.rec.width / 2;
		title.rec.y = 100 - title.rec.height / 2;
		initButton(title, title.rec, 3, 70, GREEN, DARKGRAY);

		for (int i = 0; i < maxButtons; i++)
		{
			menuButton[i].rec.width = 250;
			menuButton[i].rec.height = 70;
			menuButton[i].rec.x = 170 - menuButton[i].rec.width / 2;
			menuButton[i].rec.y = screenHeight / 2 - 100 + (120 * i) - menuButton[i].rec.height / 2;
			initButton(menuButton[i], menuButton[i].rec, 3, 50, BLANK, GREEN);
		}
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
						Gameplay::init();
						MenuManager::actualMenuScene = MenuManager::Menu;
						actualScene = GameManager::Gameplay;
						break;

					case 1:
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

					case 2:
						MenuManager::controlsActive = false;
						if (MenuManager::creditsActive)
						{
							MenuManager::mainMenuActive = true;
							MenuManager::creditsActive = false;
						}
						else
						{
							MenuManager::mainMenuActive = false;
							MenuManager::creditsActive = true;
						}
						MenuManager::actualMenuScene = MenuManager::Credits;
						break;

					case 3:
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

		drawButton("SPACE CONQUERORS", title);
		drawButton("Start", menuButton[0]);
		drawButton("Controls", menuButton[1]);
		drawButton("Credits", menuButton[2]);
		drawButton("Exit", menuButton[3]);
	}
}
}