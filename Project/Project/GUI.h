#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

class GUI
{
public:
	RenderWindow window;
	Image I_map;
	Texture T_map;
	Texture T_bar;
	Texture T_arrow;
	Texture T_line;
	Texture T_gameOver;
	Texture T_screenShot;
	Texture T_turret1;
	Texture T_turret2;
	Texture T_turret3;
	Texture T_monster1;
	Texture T_monster2;
	Texture T_missile1;
	Texture T_missile2;
	Texture T_missile3;
	Texture T_cursor1;
	Texture T_cursor2;
	Texture T_cursor3;
	Texture T_cursor4;
	Vector2f mousePosition;
	Sprite screenShot;
	Sprite bar;
	Sprite arrow;
	Sprite gameOver;
	CircleShape circle;
	Sprite cursor;
	Sprite map;

	Vector2f vectorTurret1 = Vector2f(38, 670);
	Vector2f vectorTurret2 = Vector2f(200, 670);
	Vector2f vectorTurret3 = Vector2f(360, 670);
	vector<Sprite> lines;

	Font font;
	Text texts[9];				//0 - damage, 1 - range, 2 - rate, 3 - price1, 4 - price2, 5 - price3, 6 - cash, 7 - kills, 8 - waves


	void loadGraphics();

	void display();

	void end();
};

