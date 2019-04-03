#pragma once
#include <SFML/Graphics.hpp>
#include "Monster.h"
#include <vector>

class Rocket
{
public:
	int speed;
	int damage;
	int rotationSpeed;
	int numberOfMonster;
	sf::Sprite picture;

	Rocket(int, int, int, int, int, sf::Texture &, sf::Vector2f);
	bool move(std::vector<Monster> &, int &, int &);
	bool checkCollision(std::vector<Monster> &, int &, int &);
	int getDamage();
};

