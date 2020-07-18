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

	struct TickBox {
		Rectangle outerRec;
		Rectangle innerRec;
		float linesThick;
		bool active;
		Color outerColor;
		Color innerColor;
	};

	void initTickBox(TickBox &tickBox, float size, float posX, float posY, float edgeThick, bool active, Color linesColor);
	void tickBoxCollision(TickBox &tickBox);
	void drawTickBox(TickBox tickBox);

	void initButton(Button &button, Rectangle buttonRec, int lineThick, int fontSize, Color primaryColor, Color secondaryColor);
	void updateButton(Button &button, Color mouseOutOfButton, Color mouseOverButton);
	void drawButton(const char *text, Button button);

	void drawProText(const char *text, float posX, float posY, int fontSize, Color textColor);

}

namespace Textures {

	void drawProTexture(Texture2D texture, float posX, float posY, Color color);
}	
}


#endif
