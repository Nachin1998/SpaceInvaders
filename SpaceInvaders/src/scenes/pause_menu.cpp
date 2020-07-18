#include "pause_menu.h"
#include "managers\game_manager.h"
#include "scenes\gameplay.h"

#include "utility\utility.h"

namespace MyGame {
namespace PauseMenu {
using namespace GameManager;
using namespace UI;

	static Button pauseMenu;
	static Button resume;
	static Button nextLevel;
	static Button restart;
	static Button toMenu;

	void init() {

		pauseMenu.rec.width = 350;
		pauseMenu.rec.height = 500;
		pauseMenu.rec.x = screenWidth / 2 - pauseMenu.rec.width / 2;
		pauseMenu.rec.y = screenHeight / 2 - pauseMenu.rec.height / 2;
		initButton(pauseMenu, pauseMenu.rec, 3, 0, DARKGREEN, GREEN);

		resume.rec.width = 270;
		resume.rec.height = 50;
		resume.rec.x = screenWidth / 2 - resume.rec.width / 2;
		resume.rec.y = 390 - resume.rec.height / 2;
		initButton(resume, resume.rec, 3, 30, BLANK, GREEN);

		nextLevel.rec.width = 270;
		nextLevel.rec.height = 50;
		nextLevel.rec.x = screenWidth / 2 - nextLevel.rec.width / 2;
		nextLevel.rec.y = 480 - nextLevel.rec.height / 2;
		initButton(nextLevel, nextLevel.rec, 3, 30, BLANK, GREEN);

		restart.rec.width = 270;
		restart.rec.height = 50;
		restart.rec.x = screenWidth / 2 - restart.rec.width / 2;
		restart.rec.y = 570 - restart.rec.height / 2;
		initButton(restart, restart.rec, 3, 30, BLANK, GREEN);

		toMenu.rec.width = 270;
		toMenu.rec.height = 50;
		toMenu.rec.x = screenWidth / 2 - toMenu.rec.width / 2;
		toMenu.rec.y = 660 - toMenu.rec.height / 2;
		initButton(toMenu, toMenu.rec, 3, 25, BLANK, GREEN);
	}

	void update() {
		Vector2 mousePos = GetMousePosition();

		updateButton(resume, BLANK, DARKGRAY);
		if (CheckCollisionPointRec(mousePos, resume.rec))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				Gameplay::paused = false;
			}
		}

		updateButton(nextLevel, BLANK, DARKGRAY);
		if (CheckCollisionPointRec(mousePos, nextLevel.rec))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				int nextLevel = static_cast<int>(Gameplay::level);
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
			}
		}

		updateButton(restart, BLANK, DARKGRAY);
		if (CheckCollisionPointRec(mousePos, restart.rec))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				Gameplay::init();
			}
		}

		updateButton(toMenu, BLANK, DARKGRAY);
		if (CheckCollisionPointRec(mousePos, toMenu.rec))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				init();
				GameManager::actualScene = GameManager::MainMenu;
			}
		}
	}

	void draw() {

		drawButton("", pauseMenu);
		drawProText("Paused", screenWidth / 2, screenHeight / 2 - 200, 60, GREEN);
		drawButton("Resume", resume);
		drawButton("Next Level", nextLevel);
		drawButton("Play Again", restart);
		drawButton("Back to Main Menu", toMenu);
	}
}
}