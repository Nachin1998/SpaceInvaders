#include "Utility.h"

namespace MyGame {
namespace UI {

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

	void drawProText(const char *text, int posX, int posY, int fontSize, Color textColor) {

		DrawText(text, posX - (MeasureText(text, fontSize) / 2), posY - fontSize / 2, fontSize, textColor);
	}
}

namespace Textures {

	void drawProTexture(Texture2D texture, float posX, float posY, Color color) {

		DrawTexture(texture, posX - texture.width / 2, posY - texture.height / 2, color);
	}
}
}