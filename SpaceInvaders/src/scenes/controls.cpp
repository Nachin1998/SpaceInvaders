#include "controls.h"

#include "managers\menu_manager.h"
#include "managers\game_manager.h"
#include "utility\utility.h"

namespace MyGame {
namespace Controls {
using namespace GameManager;
using namespace UI;

	static Button title;
	static Button subTitle1;
	static Button subTitle2;
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

		title.rec.width = 310;
		title.rec.height = 70;
		title.rec.x = screenWidth / 2 + 155 - title.rec.width / 2;
		title.rec.y = screenHeight / 2 - 250 - title.rec.height / 2;
		initButton(title, title.rec, 3, 50, titleColor, titleSecondaryColor);

		subTitle1.rec.width = 180;
		subTitle1.rec.height = 50;
		subTitle1.rec.x = screenWidth / 2 + 155 - subTitle1.rec.width / 2;
		subTitle1.rec.y = screenHeight / 2 - 160 - subTitle1.rec.height / 2;
		initButton(subTitle1, subTitle1.rec, 3, 35, titleColor, titleSecondaryColor);

		subTitle2.rec.width = 180;
		subTitle2.rec.height = 50;
		subTitle2.rec.x = screenWidth / 2 + 155 - subTitle2.rec.width / 2;
		subTitle2.rec.y = screenHeight / 2 + 100 - subTitle2.rec.height / 2;
		initButton(subTitle2, subTitle2.rec, 3, 35, titleColor, titleSecondaryColor);

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
				MenuManager::controlsActive = false;
			}
		}
	}

	void draw() {

		DrawRectangleLinesEx(menuBox, 6, GREEN);

		drawButton("CONTROLS", title);
		drawButton("Actions", subTitle1);
		drawButton("Rules", subTitle2);
		drawButton("Close", close);

		drawProText("Press A/D to move", subTitle1.rec.x + subTitle1.rec.width / 2, subTitle1.rec.y + subTitle1.rec.height / 2 + 60, textFontSize, textColor);
		drawProText("sideways", subTitle1.rec.x + subTitle1.rec.width / 2, subTitle1.rec.y + subTitle1.rec.height / 2 + 60 + lineBelowDistance, textFontSize, textColor);
		drawProText("Press 'Space' to", subTitle1.rec.x + subTitle1.rec.width / 2, subTitle1.rec.y + subTitle1.rec.height / 2 + 70 + lineBelowDistance * 2, textFontSize, textColor);
		drawProText("shoot lasers", subTitle1.rec.x + subTitle1.rec.width / 2, subTitle1.rec.y + subTitle1.rec.height / 2 + 70 + lineBelowDistance * 3, textFontSize, textColor);

		drawProText("Destoy all the aliens before", subTitle2.rec.x + subTitle2.rec.width / 2, subTitle2.rec.y + subTitle2.rec.height / 2 + 60, textFontSize, textColor);
		drawProText("they overwhelm you", subTitle2.rec.x + subTitle2.rec.width / 2, subTitle2.rec.y + subTitle2.rec.height / 2 + 60 + lineBelowDistance, textFontSize, textColor);
		drawProText("and shoot you down", subTitle2.rec.x + subTitle2.rec.width / 2, subTitle2.rec.y + subTitle2.rec.height / 2 + 60 + lineBelowDistance * 2, textFontSize, textColor);
		drawProText("Take them down before", subTitle2.rec.x + subTitle2.rec.width / 2, subTitle2.rec.y + subTitle2.rec.height / 2 + 70 + lineBelowDistance * 3, textFontSize, textColor);
		drawProText("they get to close", subTitle2.rec.x + subTitle2.rec.width / 2, subTitle2.rec.y + subTitle2.rec.height / 2 + 70 + lineBelowDistance * 4, textFontSize, textColor);
	}
}
}