#include"Game.h"

int main(void)
{
	Game game;
	if (game.init())
		game.run();
}