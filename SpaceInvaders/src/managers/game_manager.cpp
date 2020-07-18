#include "game_manager.h"

#include "raylib.h"

#include "managers\menu_manager.h"
#include "scenes\gameplay.h"
#include "scenes\game_over.h"

namespace MyGame {
namespace GameManager {

	static void init();
	static void update();
	static void draw();
	static void deInit();

	bool endGame = false;

	Music backgroundMusic;

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
		SetTargetFPS(60);
		SetExitKey(KEY_F4);
		InitAudioDevice();

		backgroundMusic = LoadMusicStream("res/music/BaseMusic.ogg");
		MenuManager::init();
		Gameplay::init();
		GameOver::init();

		PlayMusicStream(backgroundMusic);
		SetMusicVolume(backgroundMusic, 1.0f);
	}

	void update() {

		UpdateMusicStream(backgroundMusic);
		switch (actualScene)
		{
		case MainMenu:
			MenuManager::update();
			break;

		case Gameplay:
			Gameplay::update();
			break;

		case GameOver:
			GameOver::update();
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
			MenuManager::draw();
			break;

		case Gameplay:
			Gameplay::draw();
			break;

		case GameOver:
			GameOver::draw();
			break;

		default:
			break;
		}

		EndDrawing();
	}

	void deInit() {

		MenuManager::deInit();
		Gameplay::deInit();
		UnloadMusicStream(backgroundMusic);
		CloseAudioDevice();
		CloseWindow();
	}
}
}