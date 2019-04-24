#include <string>
#include "Button.h"

#include <iostream>

using namespace std;
using namespace sf;

Button::Button(const Texture & _picture, const Font & font, const Vector2f _position, const string & _text)
{
	picture.setTexture(_picture);
	picture.setOrigin(picture.getGlobalBounds().width / 2, picture.getGlobalBounds().height / 2);
	picture.setPosition(_position);

	text.setFont(font);
	text.setCharacterSize(36);
	text.setFillColor(Color::Black);
	//text.setStyle(Text::Bold);
	text.setString(_text);
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height);
	text.setPosition(_position);
}

void Button::display(RenderWindow & window)			//wyswietlanie przycisku
{
	window.draw(picture);			//rysowanie przycisku
	window.draw(text);				//rysowanie napisu na przycisku
}

bool Button::contains(const sf::Vector2f & _position)
{
	return picture.getGlobalBounds().contains(_position);
}
