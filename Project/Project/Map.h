#pragma once
#include <SFML/System/Vector2.hpp>

class Map		//klasa przechowujaca informacje o punktach, w ktorych potwory musza zmienic kierunek
{
public:
	const sf::Vector2f position;		//punkt, w kt�rym nalezy zmienic kierunek powtora 
	const int newDirection;		//nowy kierunek potwora
};

