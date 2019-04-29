#pragma once
#include "Rocket.h"

class Rocket1 : public Rocket			//rakieta wiezyczki nr 1
{
	int rotationSpeed = 2;		//predkosc obracania pocisku

public:
	Rocket1(const int & _id, const int & _speed, const int & _damage, const int & _rotation, const int & _numberOfMonster, sf::Texture & _picture, sf::Vector2f _position);		//konstruktor tworzacy pocisk (rakieta)
	bool specialAbilities(std::vector<Monster> & monsters, int & cash, int & kills);			//specjalne zdolnosci tego typu pocisku (rakieta)
};

