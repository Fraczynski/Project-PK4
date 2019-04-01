#pragma once
#include <SFML/Graphics.hpp>

class Stats
{
	int number = 0;
public:
	sf::Text text;
	Stats(sf::Vector2f, sf::Font );
	void display(sf::RenderWindow &);
	void editNumber(const int & _number);
};

