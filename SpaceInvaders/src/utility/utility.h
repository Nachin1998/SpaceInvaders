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

	void InitTickBox(TickBox &tickBox, float size, float posX, float posY, float edgeThick, bool active, Color linesColor);
	void tickBoxCollision(TickBox &tickBox);
	void DrawTickBox(TickBox tickBox);

	void InitButton(Button &button, Rectangle buttonRec, int lineThick, int fontSize, Color primaryColor, Color secondaryColor);
	void UpdateButton(Button &button, Color mouseOutOfButton, Color mouseOverButton);
	void DrawButton(const char *text, Button button);

	void DrawProText(const char *text, float posX, float posY, int fontSize, Color textColor);

}

namespace Textures {

	void DrawProTexture(Texture2D texture, float posX, float posY, Color color);
}	
}


#endif
