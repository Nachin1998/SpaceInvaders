#include "gameplay.h"

#include "raylib.h"
#include <iostream>

#include "player.h"
#include "invaders.h"

namespace MyGame {
namespace Gameplay {
	
	static void collisionManager();

	void init() {

		Player::init();
		Invaders::init();
	}

	void update() {

		Player::update();
		Invaders::update();

		collisionManager();
	}

	void draw() {

		Player::draw();
		Invaders::draw();
	}

	void deInit() {

		Player::deInit();
		Invaders::deInit();
	}

	void collisionManager() {

		for (int i = 0; i < Invaders::maxInvadersY; i++)
		{
			for (int j = 0; j < Invaders::maxInvadersX; j++)
			{
				if (CheckCollisionRecs(Player::bullet.rec, Invaders::invaders[i][j].body))
				{
					if (Invaders::invaders[i][j].active)
					{
						Invaders::activeInvaderCounter--;
						Invaders::invaders[i][j].active = false;
						Player::bullet.active = false;

						switch (i)
						{
						case 0:
							Player::player.points += 300;
							break;
						case 1:
						case 2:
							Player::player.points += 200;
							break;

						case 3:
						case 4:
							Player::player.points += 100;
							break;

						default:
							break;
						}
						std::cout << "Puntos: "<<Player::player.points << std::endl;
						std::cout << "Invaders active: "<<Invaders::activeInvaderCounter << std::endl;
					}
				}
			}
		}

		if (CheckCollisionRecs(Player::bullet.rec, Invaders::bullet.rec))
		{
			Player::bullet.active = false;
			Invaders::bullet.active = false;
		}
	}
}
}