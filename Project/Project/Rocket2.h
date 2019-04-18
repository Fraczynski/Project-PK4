#pragma once
#include "Rocket.h"

class Rocket2 : public Rocket
{
public:
	Rocket2(int _speed, int _damage, int _rotation, int _numberOfMonster, sf::Texture & _picture, sf::Vector2f _position);		//konstruktor tworzacy pocisk (kulka)
	bool specialAbilities(std::vector<Monster> & monsters, int & cash, int & kills);				//specjalne zdolnosci tego typu pocisku (kulka)
};

