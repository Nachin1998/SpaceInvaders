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
		Color edgesColor;
		Color textColor;
	};

	void initButton(Button button, Rectangle buttonRec, int lineThick, int fontSize, Color buttonColor, Color edgesColor, Color textColor);
	void updateButton(Button &button, Color mouseOverButton, Color mouseOutOfButton);
	void drawButton(const char *text, Button button);

	void drawProText(const char *text, int posX, int posY, int fontSize, Color textColor);

}

namespace Textures {

	void drawProTexture(Texture2D texture, float posX, float posY, Color color);
}	
}


#endif
