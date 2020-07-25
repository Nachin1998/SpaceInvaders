#include "game_over.h"

#include "managers\game_manager.h"
#include "managers\menu_manager.h"
#include "scenes\gameplay.h"

#include "entities\player.h"

#include "utility\utility.h"
#include <iostream>

namespace MyGame {
	namespace GameOver {
		using namespace GameManager;
		using namespace UI;

		static const int maxButtons = 4;

		static Button title;
		static Button gameOverButtons[maxButtons];

		static bool levelsOver = false;

		void init() {

			title.rec.width = 420;
			title.rec.height = 80;
			title.rec.x = screenWidth / 2 - title.rec.width / 2;
			title.rec.y = 80 - title.rec.height / 2;
			initButton(title, title.rec, 3, 60, GREEN, DARKGRAY);

			for (int i = 0; i < maxButtons; i++)
			{
				gameOverButtons[i].rec.width = 420;
				gameOverButtons[i].rec.height = 80;
				gameOverButtons[i].rec.x = screenWidth / 2 - gameOverButtons[i].rec.width / 2;
				gameOverButtons[i].rec.y = 500 + (i * 100) - gameOverButtons[i].rec.height / 2;
				initButton(gameOverButtons[i], gameOverButtons[i].rec, 3, 40, BLANK, GREEN);
			}
		}

		void update() {

			Vector2 mousePos = GetMousePosition();

			if (Gameplay::level != Gameplay::Four)
			{
				levelsOver = false;
			}
			int level = static_cast<int>(Gameplay::level);

			for (int i = 0; i < maxButtons; i++)
			{
				updateButton(gameOverButtons[i], BLANK, DARKGRAY);

				if (CheckCollisionPointRec(mousePos, gameOverButtons[i].rec))
				{
					if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
					{
						switch (i)
						{
						case 0:
							Gameplay::init();
							GameManager::actualScene = GameManager::Gameplay;
							break;

						case 1:
							
							if (!levelsOver)
							{								
								if (level == 3)
								{
									levelsOver = true;
								}
								else
								{
									level++;
								}

								Gameplay::level = static_cast<Gameplay::Levels>(level);
								GameManager::actualScene = GameManager::Gameplay;
								Gameplay::init();
							}

							break;

						case 2:
							Gameplay::init();
							GameManager::actualScene = GameManager::MainMenu;
							MenuManager::creditsActive = true;
							MenuManager::actualMenuScene = MenuManager::Credits;
							break;

						case 3:
							Gameplay::init();
							GameManager::actualScene = GameManager::MainMenu;
							break;

						default:
							break;
						}						
					}
				}
			}
		}

		void draw() {

			if (!Player::player.isDead)
			{
				drawButton("You won!", title);
			}
			else
			{
				drawButton("You lost!", title);
			}

			drawProText(FormatText("Points: %i", Player::player.points), screenWidth / 2, screenHeight / 2 - 200, 50, GREEN);

			drawButton("Play Again", gameOverButtons[0]);
			if (!levelsOver)
			{
				drawButton("Next Level", gameOverButtons[1]);
			}
			drawButton("Credits", gameOverButtons[2]);
			drawButton("Back to Main Menu", gameOverButtons[3]);
		}
	}
}