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

	void Init() {

		title.rec.width = 420;
		title.rec.height = 80;
		title.rec.x = screenWidth / 2 - title.rec.width / 2;
		title.rec.y = 80 - title.rec.height / 2;
		InitButton(title, title.rec, 3, 60, GREEN, DARKGRAY);

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

			InitButton(subTitle[i], subTitle[i].rec, 3, subtitleFontSize, GREEN, DARKGRAY);
		}

		back.rec.width = 200;
		back.rec.height = 70;
		back.rec.x = screenWidth / 2 - back.rec.width / 2;
		back.rec.y = screenHeight / 2 + 400 - back.rec.height / 2;
		InitButton(back, back.rec, 3, 50, BLANK, GREEN);
	}

	void Update() {

		Vector2 mousePos = GetMousePosition();

		UpdateButton(back, BLANK, DARKGRAY);
		if (CheckCollisionPointRec(mousePos, back.rec))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{				
				MenuManager::actualMenuScene = MenuManager::Menu;
				MenuManager::creditsActive = false;
			}
		}
	}

	void Draw() {

		DrawButton("CREDITS", title);
		DrawButton("Lead Programmer", subTitle[0]);
		DrawButton("Music & SFX", subTitle[1]);
		DrawButton("Art", subTitle[2]);
		DrawButton("Programs Used", subTitle[3]);
		DrawButton("Back", back);

		DrawProText("Ignacio Fernandez Lemos", subTitle[0].rec.x + subTitle[0].rec.width / 2, subTitle[0].rec.y + 100, textFontSize, GREEN);
		DrawProText("Ignacio Fernandez Lemos", subTitle[1].rec.x + subTitle[1].rec.width / 2, subTitle[1].rec.y + 100, textFontSize, GREEN);
		DrawProText("Ignacio Fernandez Lemos", subTitle[2].rec.x + subTitle[2].rec.width / 2, subTitle[2].rec.y + 100, textFontSize, GREEN);

		DrawProText("Visual Studio c++", subTitle[3].rec.x + subTitle[3].rec.width / 2, subTitle[3].rec.y + 100, textFontSize, GREEN);
		DrawProText("Raylib Library", subTitle[3].rec.x + subTitle[3].rec.width / 2, subTitle[3].rec.y + 100 + 50, textFontSize, GREEN);
	}
}
}