#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"

using namespace std;

int main()
{
	Game game;			//utworzenie obiektu gry
	game.gameLoop();		//wywolanie glownej funkcji gry
	return 0;
}
