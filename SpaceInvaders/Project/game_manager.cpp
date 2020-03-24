#include "game_manager.h"

#include "raylib.h"

#include "player.h"

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
		SetExitKey(KEY_F4);

		Player::init();
	}

	void update() {

		switch (actualScene)
		{
		case MainMenu:
			break;

		case Gameplay:
			Player::update();
			break;

		case Credits:
			break;

		default:
			break;
		}
	}

	void draw() {

		BeginDrawing();

		ClearBackground(BLACK);
		
		switch (actualScene)
		{
		case MainMenu:
			break;

		case Gameplay:
			Player::draw();
			break;

		case Credits:
			break;

		default:
			break;
		}

		EndDrawing();
	}

	void deInit() {

		Player::deInit();
		CloseWindow();
	}
}
}