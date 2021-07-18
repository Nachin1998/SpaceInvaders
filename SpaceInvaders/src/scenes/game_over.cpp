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

		void Init() {

			title.rec.width = 420;
			title.rec.height = 80;
			title.rec.x = screenWidth / 2 - title.rec.width / 2;
			title.rec.y = 80 - title.rec.height / 2;
			InitButton(title, title.rec, 3, 60, GREEN, DARKGRAY);

			for (int i = 0; i < maxButtons; i++)
			{
				gameOverButtons[i].rec.width = 420;
				gameOverButtons[i].rec.height = 80;
				gameOverButtons[i].rec.x = screenWidth / 2 - gameOverButtons[i].rec.width / 2;
				gameOverButtons[i].rec.y = 500 + (i * 100) - gameOverButtons[i].rec.height / 2;
				InitButton(gameOverButtons[i], gameOverButtons[i].rec, 3, 40, BLANK, GREEN);
			}
		}

		void Update() {

			Vector2 mousePos = GetMousePosition();

			if (Gameplay::level != Gameplay::Four)
			{
				levelsOver = false;
			}
			int level = static_cast<int>(Gameplay::level);

			for (int i = 0; i < maxButtons; i++)
			{
				UpdateButton(gameOverButtons[i], BLANK, DARKGRAY);

				if (CheckCollisionPointRec(mousePos, gameOverButtons[i].rec))
				{
					if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
					{
						switch (i)
						{
						case 0:
							Gameplay::Init();
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
								Gameplay::Init();
							}

							break;

						case 2:
							Gameplay::Init();
							GameManager::actualScene = GameManager::MainMenu;
							MenuManager::creditsActive = true;
							MenuManager::actualMenuScene = MenuManager::Credits;
							break;

						case 3:
							Gameplay::Init();
							GameManager::actualScene = GameManager::MainMenu;
							break;

						default:
							break;
						}						
					}
				}
			}
		}

		void Draw() {

			if (!Player::player.isDead)
			{
				DrawButton("You won!", title);
			}
			else
			{
				DrawButton("You lost!", title);
			}

			DrawProText(FormatText("Points: %i", Player::player.points), screenWidth / 2, screenHeight / 2 - 200, 50, GREEN);

			DrawButton("Play Again", gameOverButtons[0]);
			if (!levelsOver)
			{
				DrawButton("Next Level", gameOverButtons[1]);
			}
			DrawButton("Credits", gameOverButtons[2]);
			DrawButton("Back to Main Menu", gameOverButtons[3]);
		}
	}
}