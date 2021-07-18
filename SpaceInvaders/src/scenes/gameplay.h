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

	void Init();
	void Update();
	void Draw();
	void DeInit();
}
}

#endif
