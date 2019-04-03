#pragma once
#include <SFML/Graphics.hpp>
#include "Monster.h"
#include <vector>

class Rocket
{
public:
	int speed;
	int damage;
	int numberOfMonster;
	sf::Sprite picture;

public:
	Rocket(int, int, int, int, sf::Texture &, sf::Vector2f);
	virtual bool specialAbilities(std::vector<Monster> &, int &, int &) = 0;
	bool checkCollision(std::vector<Monster> &, int &, int &);
	int getDamage();
	void display(sf::RenderWindow &);
};

