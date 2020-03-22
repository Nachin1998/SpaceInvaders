#include "game_manager.h"

#include "raylib.h"

namespace MyGame {
	namespace GameManager {

		static void init();
		static void update();
		static void draw();
		static void deInit();

		bool endGame = false;

		SpaceInvadersScenes actualScene = MainMenu;

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
		}

		void update() {

			switch (actualScene)
			{
			case MainMenu:
				break;

			case Gameplay:
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
				break;

			case Credits:
				break;

			default:
				break;
			}

			EndDrawing();
		}

		void deInit() {

			CloseWindow();
		}
	}
}