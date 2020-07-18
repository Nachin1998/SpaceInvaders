#include "main_menu.h"

#include "managers\menu_manager.h"
#include "managers\game_manager.h"
#include "scenes\gameplay.h"
#include "utility\utility.h"

namespace MyGame {
namespace MainMenu {
using namespace GameManager;
using namespace UI;

	static const int maxButtons = 5;

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
						if (MenuManager::optionsActive)
						{
							MenuManager::optionsActive = false;
						}
						else
						{
							MenuManager::controlsActive = false;
							MenuManager::optionsActive = true;
						}
						MenuManager::actualMenuScene = MenuManager::Options;
						break;

					case 2:
						if (MenuManager::controlsActive)
						{
							MenuManager::controlsActive = false;
						}
						else
						{
							MenuManager::optionsActive = false;
							MenuManager::controlsActive = true;
						}
						MenuManager::actualMenuScene = MenuManager::Controls;
						break;

					case 3:
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

		drawButton("SPACE CONQUERORS", title);
		drawButton("Start", menuButton[0]);
		drawButton("Options", menuButton[1]);
		drawButton("Controls", menuButton[2]);
		drawButton("Credits", menuButton[3]);
		drawButton("Exit", menuButton[4]);

		drawProText("V1.0", screenWidth - 50, screenHeight - 50, 30, GREEN);
	}
}
}