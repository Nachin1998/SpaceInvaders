#include "credits.h"

#include "managers\menu_manager.h"
#include "managers\game_manager.h"

#include "utility\utility.h"

namespace MyGame {
namespace Credits {
using namespace GameManager;
using namespace UI;

	static const int maxSubtitles = 4;

	static Button title;
	static Button subTitle[maxSubtitles];
	static Button back;

	static int subtitleFontSize = 30;
	static int textFontSize = 25;

	void init() {

		title.rec.width = 420;
		title.rec.height = 80;
		title.rec.x = screenWidth / 2 - title.rec.width / 2;
		title.rec.y = 80 - title.rec.height / 2;
		initButton(title, title.rec, 3, 60, GREEN, DARKGRAY);

		for (int i = 0; i < maxSubtitles; i++)
		{
			subTitle[i].rec.width = 300;
			subTitle[i].rec.height = 60;
			if (i % 2 == 0)
			{
				subTitle[i].rec.x = screenWidth / 2 - 230 - subTitle[i].rec.width / 2;
			}
			else
			{
				subTitle[i].rec.x = screenWidth / 2 + 230 - subTitle[i].rec.width / 2;
			}
			if (i < 2)
			{
				subTitle[i].rec.y = 190 - subTitle[i].rec.height / 2;
			}
			else
			{
				subTitle[i].rec.y = 190 + 300 - subTitle[i].rec.height / 2;
			}

			initButton(subTitle[i], subTitle[i].rec, 3, subtitleFontSize, GREEN, DARKGRAY);
		}

		back.rec.width = 200;
		back.rec.height = 70;
		back.rec.x = screenWidth / 2 - back.rec.width / 2;
		back.rec.y = screenHeight / 2 + 400 - back.rec.height / 2;
		initButton(back, back.rec, 3, 50, BLANK, GREEN);
	}

	void update() {

		Vector2 mousePos = GetMousePosition();

		updateButton(back, BLANK, DARKGRAY);
		if (CheckCollisionPointRec(mousePos, back.rec))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{				
				MenuManager::creditsActive = false;
				MenuManager::mainMenuActive = true;
			}
		}
	}

	void draw() {

		drawButton("CREDITS", title);
		drawButton("Lead Programmer", subTitle[0]);
		drawButton("Music & SFX", subTitle[1]);
		drawButton("Art", subTitle[2]);
		drawButton("Programs Used", subTitle[3]);
		drawButton("Back", back);

		drawProText("Ignacio Fernandez Lemos", subTitle[0].rec.x + subTitle[0].rec.width / 2, subTitle[0].rec.y + 100, textFontSize, GREEN);
		drawProText("Ignacio Fernandez Lemos", subTitle[1].rec.x + subTitle[1].rec.width / 2, subTitle[1].rec.y + 100, textFontSize, GREEN);
		drawProText("Ignacio Fernandez Lemos", subTitle[2].rec.x + subTitle[2].rec.width / 2, subTitle[2].rec.y + 100, textFontSize, GREEN);

		drawProText("Visual Studio c++", subTitle[3].rec.x + subTitle[3].rec.width / 2, subTitle[3].rec.y + 100, textFontSize, GREEN);
		drawProText("Raylib Library", subTitle[3].rec.x + subTitle[3].rec.width / 2, subTitle[3].rec.y + 100 + 50, textFontSize, GREEN);
	}
}
}