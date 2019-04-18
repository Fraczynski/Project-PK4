#pragma once
#include <SFML/System/Vector2.hpp>

class Map		//klasa przechowujaca informacje o punktach, w ktorych potwory musza zmienic kierunek
{
public:
	sf::Vector2f position;		//punkt, w którym nalezy zmienic kierunek powtora 
	int newDirection;		//nowy kierunek potwora
};

