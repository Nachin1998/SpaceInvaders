#ifndef GAMEPLAY_H
#define GAMEPLAY_H

namespace MyGame{
namespace Gameplay{
	
	enum Levels
	{
		One,
		Two,
		Three,
		Four
	};
	extern Levels level;

	extern bool paused;

	void init();
	void update();
	void draw();
	void deInit();
}
}

#endif
