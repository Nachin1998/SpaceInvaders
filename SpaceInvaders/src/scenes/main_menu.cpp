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

	void Init() {

		title.rec.width = 800;
		title.rec.height = 100;
		title.rec.x = screenWidth / 2 - title.rec.width / 2;
		title.rec.y = 100 - title.rec.height / 2;
		InitButton(title, title.rec, 3, 70, GREEN, DARKGRAY);

		for (int i = 0; i < maxButtons; i++)
		{
			menuButton[i].rec.width = 250;
			menuButton[i].rec.height = 70;
			menuButton[i].rec.x = 170 - menuButton[i].rec.width / 2;
			menuButton[i].rec.y = screenHeight / 2 - 100 + (120 * i) - menuButton[i].rec.height / 2;
			InitButton(menuButton[i], menuButton[i].rec, 3, 50, BLANK, GREEN);
		}
	}

	void Update() {

		Vector2 mousePos = GetMousePosition();

		for (int i = 0; i < maxButtons; i++)
		{
			UpdateButton(menuButton[i], BLANK, DARKGRAY);

			if (CheckCollisionPointRec(mousePos, menuButton[i].rec))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					switch (i)
					{
					case 0:
						Gameplay::level = Gameplay::One;
						MenuManager::actualMenuScene = MenuManager::Menu;
						actualScene = GameManager::Gameplay;
						break;

					case 1:
						if (MenuManager::actualMenuScene == MenuManager::Options)
						{
							MenuManager::actualMenuScene = MenuManager::Menu;
						}
						else
						{
							MenuManager::actualMenuScene = MenuManager::Options;
						}
						break;

					case 2:
						if (MenuManager::actualMenuScene == MenuManager::Controls)
						{
							MenuManager::actualMenuScene = MenuManager::Menu;
						}
						else
						{
							MenuManager::actualMenuScene = MenuManager::Controls;
						}
						break;

					case 3:
						MenuManager::creditsActive = true;
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

	void Draw() {

		DrawButton("SPACE CONQUERORS", title);
		DrawButton("Start", menuButton[0]);
		DrawButton("Options", menuButton[1]);
		DrawButton("Controls", menuButton[2]);
		DrawButton("Credits", menuButton[3]);
		DrawButton("Exit", menuButton[4]);

		DrawProText("V1.0", screenWidth - 50, screenHeight - 50, 30, GREEN);
	}
}
}