#pragma once
#include <SFML/Graphics.hpp>
#include "Monster.h"
#include "Rocket.h"
#include <vector>

class Rocket2 : public Rocket
{
public:
	Rocket2(int, int, int, int, sf::Texture &, sf::Vector2f);
	bool specialAbilities(std::vector<Monster> &, int &, int &);
};

