#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>
#include <vector>

#include "Character.h"
#include "Projectile.h";
#include "TextureManager.h"
#include "Pointer.h"
#include "FloatingText.h"

using namespace sf;
using namespace std;

const float PLAYER_SPEED = 0.08;
const float LVL_X_LIMIT = 2000;
const float LVL_Y_LIMIT = 2000;

class Game
{
public:
	Game();
	~Game();

	bool init(void);
	void run(void);

private:
	RenderWindow window;
	View view;
	Character player;
	Pointer cursor;

};

#endif