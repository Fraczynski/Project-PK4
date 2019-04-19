#pragma once
#include "Rocket.h"

class Rocket2 : public Rocket
{
public:
	Rocket2(const int & _id, const int & _speed, const int & _damage, const int & _rotation, const int & _numberOfMonster, sf::Texture & _picture, sf::Vector2f _position);		//konstruktor tworzacy pocisk (kulka)
	bool specialAbilities(std::vector<Monster> & monsters, int & cash, int & kills);				//specjalne zdolnosci tego typu pocisku (kulka)
};

