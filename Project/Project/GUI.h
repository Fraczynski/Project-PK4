#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

class Monster
{
public:
	int HP;
	int level;
	float speed = 1;
	int direction = 0;
	sf::Text hp;
	sf::Sprite picture;

	Monster(int, sf::Font &, sf::Texture &, sf::Vector2f);
	int move(const Map []);		//map niepotrzebne
	bool hurt(int);
	void display(sf::RenderWindow &);
	int getLevel();
};

