#include "pause_menu.h"
#include "managers\game_manager.h"
#include "scenes\gameplay.h"

#include "utility\utility.h"

namespace MyGame {
namespace PauseMenu {
	using namespace GameManager;
	using namespace UI;

	const int maxButtons = 4;

	static Button pauseMenu;
	static Button pauseButtons[maxButtons];

	void init() {

		pauseMenu.rec.width = 350;
		pauseMenu.rec.height = 500;
		pauseMenu.rec.x = screenWidth / 2 - pauseMenu.rec.width / 2;
		pauseMenu.rec.y = screenHeight / 2 - pauseMenu.rec.height / 2;
		initButton(pauseMenu, pauseMenu.rec, 3, 0, DARKGREEN, GREEN);

		for (int i = 0; i < maxButtons; i++)
		{
			pauseButtons[i].rec.width = 300;
			pauseButtons[i].rec.height = 50;
			pauseButtons[i].rec.x = screenWidth / 2 - pauseButtons[i].rec.width / 2;
			pauseButtons[i].rec.y = 390 + (i * 90) - pauseButtons[i].rec.height / 2;
			initButton(pauseButtons[i], pauseButtons[i].rec, 3, 30, BLANK, GREEN);
		}
	}

	void update() {
		Vector2 mousePos = GetMousePosition();

		for (int i = 0; i < maxButtons; i++)
		{
			updateButton(pauseButtons[i], BLANK, DARKGRAY);

			if (CheckCollisionPointRec(mousePos, pauseButtons[i].rec))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					int nextLevel = static_cast<int>(Gameplay::level);
					switch (i)
					{
					case 0:
						Gameplay::paused = false;
						break;

					case 1:
						if (nextLevel == 3)
						{
							nextLevel = 0;
						}
						else
						{
							nextLevel++;
						}

						Gameplay::level = static_cast<Gameplay::Levels>(nextLevel);

						Gameplay::init();
						break;

					case 2:
						Gameplay::init();
						break;

					case 3:
						Gameplay::init();
						GameManager::actualScene = GameManager::MainMenu;
						break;
					}
				}
			}
		}
	}

	void draw() {

		drawButton("", pauseMenu);
		drawProText("Paused", screenWidth / 2, screenHeight / 2 - 200, 60, GREEN);

		drawButton("Resume", pauseButtons[0]);
		drawButton("Next Level", pauseButtons[1]);
		drawButton("Play Again", pauseButtons[2]);
		drawButton("Back to Main Menu", pauseButtons[3]);
	}
}
}