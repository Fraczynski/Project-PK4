#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"

using namespace std;

int main()
{
	Game game;				//utworzenie obiektu gry
	//petla wykonujaca sie dopoki nie zostanie zakonczona gra
	while (game.isPlayed())
	{
		game.events();
		game.move_monsters();
		game.add_monsters();
		game.rotate_turrets();
		game.shoot();
		game.move_missiles();
		game.moveTurret();
		game.guiMethods();
	}
	return 0;
}