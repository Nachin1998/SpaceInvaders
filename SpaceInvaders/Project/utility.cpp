#include "Utility.h"

namespace MyGame {
namespace UI {

	void initButton(Button button, Rectangle buttonRec, int lineThick, int fontSize, Color buttonColor, Color edgesColor, Color textColor) {

		button.rec = buttonRec;
		button.lineThick = lineThick;
		button.fontSize = fontSize;
		button.buttonColor = buttonColor;
		button.edgesColor = edgesColor;
		button.textColor = textColor;
	}

	void updateButton(Button &button, Color mouseOverButton, Color mouseOutOfButton) {

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
		DrawRectangleLinesEx(button.rec, button.lineThick, button.edgesColor);
		drawProText(text, static_cast<int>(button.rec.x), static_cast<int>(button.rec.y), button.fontSize, button.textColor);
	}

	void drawProText(const char *text, int posX, int posY, int fontSize, Color textColor) {

		DrawText(text, posX - MeasureText(text, fontSize) / 2, posY, fontSize, textColor);
	}
}

namespace Textures {

	void drawProTexture(Texture2D texture, float posX, float posY, Color color) {

		DrawTexture(texture, posX - texture.width / 2, posY - texture.height / 2, color);
	}
}
	
}