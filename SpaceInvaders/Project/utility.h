#ifndef UTILITY_H
#define UTILITY_H

#include "raylib.h"

namespace MyGame {
namespace UI {

	struct Button {
		Rectangle rec;
		int lineThick;
		int fontSize;
		Color buttonColor;
		Color secondaryColor;
	};

	void initButton(Button &button, Rectangle buttonRec, int lineThick, int fontSize, Color primaryColor, Color secondaryColor);
	void updateButton(Button &button, Color mouseOutOfButton, Color mouseOverButton);
	void drawButton(const char *text, Button button);

	void drawProText(const char *text, int posX, int posY, int fontSize, Color textColor);

}

namespace Textures {

	void drawProTexture(Texture2D texture, float posX, float posY, Color color);
}	
}


#endif
