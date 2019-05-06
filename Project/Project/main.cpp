#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"

using namespace std;

int main()
{
	Game game;				//utworzenie obiektu gry
	game.loadGraphics();
	game.resetGame();
	game.display();

	while (game.isPlayed())				//petla wykonujaca sie dopoki nie zostanie zakonczona gra
	{
		game.events();
		game.add_monsters();
		game.rotate_turrets();
		game.shoot();
		game.move_missiles();
		game.move_monsters();
		game.moveTurret();
		game.updateClock();
		game.display();
		game.end();
	}
	return 0;
}