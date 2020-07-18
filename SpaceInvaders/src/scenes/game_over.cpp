 #include "game_over.h"

#include "managers\game_manager.h"
#include "managers\menu_manager.h"
#include "scenes\gameplay.h"

#include "entities\player.h"

#include "utility\utility.h"

namespace MyGame {
namespace GameOver {
using namespace GameManager;
using namespace UI;

	static Button title;
	static Button restart;
	static Button toCredits;
	static Button toMenu;
	
	void init() {

		title.rec.width = 420;
		title.rec.height = 80;
		title.rec.x = screenWidth / 2 - title.rec.width / 2;
		title.rec.y = 80 - title.rec.height / 2;
		initButton(title, title.rec, 3, 60, GREEN, DARKGRAY);

		restart.rec.width = 420;
		restart.rec.height = 80;
		restart.rec.x = screenWidth / 2 - restart.rec.width / 2;
		restart.rec.y = 500 - restart.rec.height / 2;
		initButton(restart, restart.rec, 3, 40, BLANK, GREEN);

		toCredits.rec.width = 420;
		toCredits.rec.height = 80;
		toCredits.rec.x = screenWidth / 2 - toCredits.rec.width / 2;
		toCredits.rec.y = 600 - toCredits.rec.height / 2;
		initButton(toCredits, toCredits.rec, 3, 40, BLANK, GREEN);

		toMenu.rec.width = 420;
		toMenu.rec.height = 80;
		toMenu.rec.x = screenWidth / 2 - toMenu.rec.width / 2;
		toMenu.rec.y = 700 - toMenu.rec.height / 2;
		initButton(toMenu, toMenu.rec, 3, 40, BLANK, GREEN);
	}

	void update() {

		Vector2 mousePos = GetMousePosition();

		updateButton(restart, BLANK, DARKGRAY);
		if (CheckCollisionPointRec(mousePos, restart.rec))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				Gameplay::init();
				GameManager::actualScene = GameManager::Gameplay;
			}
		}

		updateButton(toCredits, BLANK, DARKGRAY);
		if (CheckCollisionPointRec(mousePos, toCredits.rec))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				MenuManager::mainMenuActive = false;
				GameManager::actualScene = GameManager::MainMenu;
				MenuManager::creditsActive = true;
				MenuManager::actualMenuScene = MenuManager::Credits;
			}
		}

		updateButton(toMenu, BLANK, DARKGRAY);
		if (CheckCollisionPointRec(mousePos, toMenu.rec))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				GameManager::actualScene = GameManager::MainMenu;
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
		
		drawButton("Play Again", restart);
		drawButton("Credits", toCredits);
		drawButton("Back to Main Menu", toMenu);
	}
}
}