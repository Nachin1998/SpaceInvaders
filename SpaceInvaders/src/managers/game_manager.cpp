#include "game_manager.h"

#include "raylib.h"

#include "managers\menu_manager.h"
#include "scenes\gameplay.h"
#include "scenes\game_over.h"

namespace MyGame {
namespace GameManager {

	static void Init();
	static void Update();
	static void Draw();
	static void DeInit();

	bool endGame = false;

	Music backgroundMusic;

	SpaceInvadersScenes actualScene = MainMenu;

	void RunGame() {

		Init();

		while (!WindowShouldClose() && !endGame)
		{
			Update();
			Draw();
		}

		DeInit();
	}

	void Init() {

		InitWindow(screenWidth, screenHeight, "Space Invaders - by Ignacio Fernández Lemos");
		SetTargetFPS(60);
		SetExitKey(KEY_F4);
		InitAudioDevice();

		backgroundMusic = LoadMusicStream("res/music/BaseMusic.ogg");
		MenuManager::Init();
		Gameplay::Init();
		GameOver::Init();

		PlayMusicStream(backgroundMusic);
		SetMusicVolume(backgroundMusic, 1.0f);
	}

	void Update() {

		UpdateMusicStream(backgroundMusic);
		switch (actualScene)
		{
		case MainMenu:
			MenuManager::Update();
			break;

		case Gameplay:
			Gameplay::Update();
			break;

		case GameOver:
			GameOver::Update();
			break;

		default:
			break;
		}
	}

	void Draw() {

		BeginDrawing();

		ClearBackground(BLACK);
		
		switch (actualScene)
		{
		case MainMenu:
			MenuManager::Draw();
			break;

		case Gameplay:
			Gameplay::Draw();
			break;

		case GameOver:
			GameOver::Draw();
			break;

		default:
			break;
		}

		EndDrawing();
	}

	void DeInit() {

		MenuManager::DeInit();
		Gameplay::DeInit();
		UnloadMusicStream(backgroundMusic);
		CloseAudioDevice();
		CloseWindow();
	}
}
}