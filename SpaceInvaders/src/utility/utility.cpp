#include "utility.h"

namespace MyGame {
namespace UI {

	void initTickBox(TickBox &tickBox, float size, float posX, float posY, float edgeThick, bool active, Color linesColor) {

		tickBox.outerRec.width = size;
		tickBox.outerRec.height = size;
		tickBox.outerRec.x = posX - tickBox.outerRec.width / 2;
		tickBox.outerRec.y = posY - tickBox.outerRec.height / 2;
		tickBox.innerRec.width = tickBox.outerRec.width - size / 2.5f;
		tickBox.innerRec.height = tickBox.outerRec.height - size / 2.5f;
		tickBox.innerRec.x = posX - tickBox.innerRec.width / 2;
		tickBox.innerRec.y = posY - tickBox.innerRec.height / 2;
		tickBox.linesThick = edgeThick;
		tickBox.active = active;
		tickBox.outerColor = LIGHTGRAY;
		tickBox.innerColor = BLANK;
	}

	void tickBoxCollision(TickBox &tickBox) {

		if (CheckCollisionPointRec(GetMousePosition(), tickBox.outerRec))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				if (tickBox.active)
				{
					tickBox.active = false;
				}
				else
				{
					tickBox.active = true;
				}
			}

			if (tickBox.active)
			{
				tickBox.outerColor = DARKGREEN;
				tickBox.innerColor = DARKGREEN;
			}
			else
			{
				tickBox.outerColor = LIGHTGRAY;
				tickBox.innerColor = LIGHTGRAY;
			}
		}
		else
		{
			if (tickBox.active)
			{
				tickBox.outerColor = GREEN;
				tickBox.innerColor = GREEN;
			}
			else
			{
				tickBox.outerColor = LIGHTGRAY;
				tickBox.innerColor = BLANK;
			}
		}
	}

	void drawTickBox(TickBox tickBox) {

		DrawRectangleLinesEx(tickBox.outerRec, static_cast<int>(tickBox.linesThick), tickBox.outerColor);
		DrawRectangleRec(tickBox.innerRec, tickBox.innerColor);
	}

	void initButton(Button &button, Rectangle buttonRec, int lineThick, int fontSize, Color buttonColor, Color secondaryColor) {

		button.rec = buttonRec;
		button.lineThick = lineThick;
		button.fontSize = fontSize;
		button.buttonColor = buttonColor;
		button.secondaryColor = secondaryColor;
	}

	void updateButton(Button &button, Color mouseOutOfButton, Color mouseOverButton) {

		if (CheckCollisionPointRec(GetMousePosition(), button.rec))
		{
			button.buttonColor = mouseOverButton;
		}
		else
		{
			button.buttonColor = mouseOutOfButton;
		}
	}

	void drawButton(const char *text, Button button) {

		DrawRectangleRec(button.rec, button.buttonColor);
		DrawRectangleLinesEx(button.rec, button.lineThick, button.secondaryColor);
		drawProText(text, button.rec.x + button.rec.width / 2, button.rec.y + button.rec.height / 2, button.fontSize, button.secondaryColor);
	}

	void drawProText(const char *text, float posX, float posY, int fontSize, Color textColor) {

		DrawText(text, static_cast<int>(posX - (MeasureText(text, fontSize) / 2)), static_cast<int>(posY - fontSize / 2), fontSize, textColor);
	}
}

namespace Textures {

	void drawProTexture(Texture2D texture, float posX, float posY, Color color) {

		DrawTexture(texture, static_cast<int>(posX - texture.width / 2), static_cast<int>(posY - texture.height / 2), color);
	}
}
}