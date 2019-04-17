#pragma once
#include <SFML/Graphics.hpp>
#include "Monster.h"
#include <vector>
#include <queue>
#include "Rest.h"

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
	std::queue<Upgrading> qDamage;
	std::queue<Upgrading> qRange;
	std::queue<Upgrading> qRate;

	Turret(int _id, int _price, int _damage, int _rate, int _range, sf::Texture & _picture, sf::Vector2f _position);
	Turret(const Turret & _turret);
	int getPrice();
	void rotate(const std::vector<Monster> &);
	int shoot(std::vector<Monster> &);
	bool isInRange(const Monster &);
	void upgrade(int upgrading, int & cash);
};

