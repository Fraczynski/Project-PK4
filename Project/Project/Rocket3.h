#pragma once
#include "Rocket.h"

class Rocket3 : public Rocket
{
	int timeOfLife;

public:
	Rocket3(int _speed, int _damage, int _rotation, int _timeOfLife, int _numberOfMonster, sf::Texture & _picture, sf::Vector2f _position);		//konstruktor tworzacy pocisk (laser)
	bool specialAbilities(std::vector<Monster> & monsters, int & cash, int & kills);			//specjalne zdolnosci tego typu pocisku (laser)
};