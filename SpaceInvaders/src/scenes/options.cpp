#include "options.h"

#include "managers\menu_manager.h"
#include "managers\game_manager.h"
#include "utility\utility.h"

namespace MyGame {
namespace Options {
	using namespace GameManager;
	using namespace UI;

	static void muteButtonUpdate();
	static TickBox muteGame;
	static Button close;

	static Rectangle menuBox;

	static int lineBelowDistance = 35;
	static int textFontSize = 30;

	static Color titleColor = GREEN;
	static Color titleSecondaryColor = DARKGRAY;
	static Color textColor = GREEN;

	void init() {

		menuBox.width = 500;
		menuBox.height = 800;
		menuBox.x = screenWidth / 2 + 155 - menuBox.width / 2;
		menuBox.y = screenHeight / 2 + 70 - menuBox.height / 2;

		UI::initTickBox(muteGame, 50.0f, screenWidth / 2 + 250, screenHeight / 2 - 25, 5, false, LIGHTGRAY);

		close.rec.width = 200;
		close.rec.height = 70;
		close.rec.x = screenWidth / 2 + 155 - close.rec.width / 2;
		close.rec.y = screenHeight / 2 + 400 - close.rec.height / 2;
		initButton(close, close.rec, 3, 50, BLANK, titleColor);
	}

	void update() {

		Vector2 mousePos = GetMousePosition();

		updateButton(close, BLANK, DARKGRAY);
		if (CheckCollisionPointRec(mousePos, close.rec))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				MenuManager::actualMenuScene = MenuManager::Menu;
			}
		}

		muteButtonUpdate();
	}

	void draw() {

		DrawRectangleLinesEx(menuBox, 6, GREEN);

		drawProText("Options", menuBox.x + menuBox.width / 2, menuBox.y + 50, textFontSize  * 2, textColor);

		drawProText("Mute sound", muteGame.innerRec.x - 130, muteGame.innerRec.y + muteGame.innerRec.height / 2, textFontSize, textColor);
		drawTickBox(muteGame);		

		drawButton("Close", close);
	}

	void muteButtonUpdate() {

		if (muteGame.active)
		{
			muteGame.outerColor = GREEN;
			muteGame.innerColor = GREEN;
			PauseMusicStream(backgroundMusic);
		}
		else
		{
			ResumeMusicStream(backgroundMusic);
		}

		UI::tickBoxCollision(muteGame);
	}
}
}