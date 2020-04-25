#include "game_manager.h"

#include "raylib.h"

#include "gameplay.h"

namespace MyGame {
namespace GameManager {

	static void init();
	static void update();
	static void draw();
	static void deInit();

	bool endGame = false;

	SpaceInvadersScenes actualScene = Gameplay;

	void runGame() {

		init();

		while (!WindowShouldClose() && !endGame)
		{
			update();
			draw();
		}

		deInit();
	}

	void init() {

		InitWindow(screenWidth, screenHeight, "Space Invaders - by Ignacio Fernández Lemos");
		SetTargetFPS(60);
		SetExitKey(KEY_F4);

		Gameplay::init();
	}

	void update() {

		switch (actualScene)
		{
		case MainMenu:
			break;

		case Gameplay:
			Gameplay::update();
			break;

		case GameOver:
			break;

		case Credits:
			break;

		default:
			break;
		}
	}

	void draw() {

		BeginDrawing();

		ClearBackground(WHITE);
		
		switch (actualScene)
		{
		case MainMenu:
			break;

		case Gameplay:
			Gameplay::draw();
			break;

		case GameOver:
			break;
		
		case Credits:
			break;

		default:
			break;
		}

		EndDrawing();
	}

	void deInit() {

		Gameplay::deInit();
		CloseWindow();
	}
}
}