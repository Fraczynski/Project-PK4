#pragma once
#include <SFML/Graphics.hpp>
#include <queue>

class Upgrading
{
	int price;
	int value;

public:
	Upgrading(int _price, int _value);
	int getPrice();
	int getValue();
};

void upgradingTurret(const int & id, std::queue<Upgrading> & qDamage, std::queue<Upgrading> & qRange, std::queue<Upgrading> & qRate);
