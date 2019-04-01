#include "Rest.h"
#include <string.h>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

Stats::Stats(Vector2f _position, Font font)
{
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(Color(0, 0, 0));
	text.setPosition(_position);
	text.setString(to_string(number));
	text.setOrigin(0, text.getGlobalBounds().height / 2);
}

void Stats::editNumber(const int & _number)
{
	number = _number;
}

void Stats::display(RenderWindow & window)
{
	window.draw(text);
}
