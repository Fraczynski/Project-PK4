#pragma once
#include <SFML/Graphics.hpp>

class Picture
{
public:
	sf::Sprite picture;

	Picture();
	Picture(const sf::Texture & _picture);
	Picture(const sf::Texture & _picture, const sf::Vector2f _position, const int & _monsterPictureX, const int & _monsterPictureY, const int & _monsterSize);
	Picture(const sf::Texture & _picture, const sf::Vector2f _position, const sf::Vector2f _scale);
	Picture(const sf::Texture & _picture, const sf::Vector2f _position, const int & _rotation);
	~Picture();

};

