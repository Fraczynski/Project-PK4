#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"
#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

int main(int argc, char * argv[])
{
	Game game;
	game.gameLoop(argc, argv);
	return 0;
}
