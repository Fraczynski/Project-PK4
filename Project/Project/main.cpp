#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"

#include <Windows.h>

using namespace std;

int main()
{
	Game game;				//utworzenie obiektu gry
	game.loadGraphics();
	/*if (!game.isPlayed())
		return 0;*/
	game.resetGame();
	game.menu();
	game.display();

	while (game.isPlayed())				//petla wykonujaca sie dopoki nie zostanie zakonczona gra
	{
		game.add_monsters();
		game.rotate_turrets();
		game.shoot();
		game.move_missiles();
		game.move_monsters();
		game.moveTurret();
		game.updateClock();
		game.display();
		game.end();
		game.events();
	}
	return 0;
}