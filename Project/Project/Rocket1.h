#pragma once
#include "Rocket.h"

class Rocket1 : public Rocket			//rakieta wiezyczki nr 1
{
	int rotationSpeed;		//predkosc obracania pocisku

public:
	Rocket1(int _speed, int _damage, int _rotation, int _rotationSpeed, int _numberOfMonster, sf::Texture & _picture, sf::Vector2f _position);		//konstruktor tworzacy pocisk (rakieta)
	bool specialAbilities(std::vector<Monster> & monsters, int & cash, int & kills);			//specjalne zdolnosci tego typu pocisku (rakieta)
};

