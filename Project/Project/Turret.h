#pragma once
#include <SFML/Graphics.hpp>
#include "Monster.h"
#include <vector>

class Turret
{
public:
	int id;
	int price;
	int timeToShoot = 0;
	int rotationSpeed = 2;
	int damage;
	int rate;
	int range;
	int aimAtMonster = -1;
	sf::Sprite picture;

	Turret(int, int, int, int, int, sf::Texture &, sf::Vector2f);
	Turret(const Turret & _turret);
	int getPrice();
	void rotate(const std::vector<Monster> &);
	int shoot(std::vector<Monster> &);
	bool isInRange(const Monster &);
};
