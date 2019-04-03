#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include <Windows.h>
#include <string.h>
#include "Monster.h"
#include "Turret.h"
#include "Rocket.h"
#include "Rocket1.h"
#include "Rocket2.h"
#include "Rocket3.h"
#include "Map.h"
#include "Icon.h"

using namespace std;
using namespace sf;

class Game
{
	Clock clock;
	Time time;

	int width = 1000;
	int height = 703;
	int timeToNextRound = 30;
	int roundTime = 1200;
	int ifMovingTurret = 0;
	int level = 0;
	int cash = 10;
	int kills = 0;
	RenderWindow window;
	Vector2f mousePosition;
	Image I_map;
	Texture T_map;
	Texture T_bar;
	Texture T_arrow;
	Texture T_line;
	Texture T_gameOver;
	Texture T_screenShot;
	Sprite screenShot;
	Sprite bar;
	Sprite arrow;
	Sprite gameOver;
	CircleShape circle;
	const Map map1[11] = { {Vector2f(920, 539), 1}, {Vector2f(83, 539), 2}, {Vector2f(83, 83), 3}, {Vector2f(815, 83), 0}, {Vector2f(815, 431), 1}, {Vector2f(190, 431), 2 }, 
					 {Vector2f(190, 188), 3}, {Vector2f(709, 188), 0}, {Vector2f(709, 323), 1}, {Vector2f(450, 323), 2}, { Vector2f(450, 295), 5 } };
	Texture T_turret1;
	Texture T_turret2;
	Texture T_turret3;
	Texture T_monster1;
	Texture T_missile1;
	Texture T_missile2;
	Texture T_missile3;
	Texture T_cursor1;
	Texture T_cursor2;
	Texture T_cursor3;
	Texture T_cursor4;
	Sprite cursor;
	Sprite map;
	Turret *turret1;
	Turret *turret2;
	Turret *turret3;
	Vector2f vectorTurret1 = Vector2f(38, 670);
	Vector2f vectorTurret2 = Vector2f(200, 670);
	Vector2f vectorTurret3 = Vector2f(360, 670);

	Font font;
	Text T_cash;
	Text T_kills;
	Text T_waves;

	vector<Monster> monsters;
	vector<Turret> turrets;
	vector<Rocket *> rockets;
	vector<Sprite> lines;


public:
	void gameLoop(int argc, char * argv[]);

	void loadGraphics();

	void events();

	void leftButtonPressed();

	void movingTurret();

	void notMovingTurret();

	void display();

	void updateClock();

	void move_monsters();

	void add_monsters(int);

	void rotate_turrets();

	void move_rockets();

	bool checkPlace(Vector2f, int, int);

	void shoot();

	void end();

	void fps();

	void cleaner();
};