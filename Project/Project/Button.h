#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button			//klasa reprezentujaca wiezyczke
{
	sf::Sprite picture;
	sf::Text text;
public:
	Button(const sf::Texture & _picture, const sf::Font & font, const sf::Vector2f _position, const std::string & _text, sf::Vector2f scale = sf::Vector2f(1, 1));
	void display(sf::RenderWindow & window);				//wyswietlanie przycisku
	bool contains(const sf::Vector2f & _position);			//sprawdzanie, czy dany punkt zawiera sie w obrazku przycisku
};