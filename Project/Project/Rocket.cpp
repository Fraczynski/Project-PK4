#include "Rocket.h"
#include <string.h>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

Rocket::Rocket(int _speed, int _damage, int _rotation, int _numberOfMonster, Texture & _picture, Vector2f _position) :
			   speed(_speed), damage(_damage), numberOfMonster(_numberOfMonster)
{
	picture.setTexture(_picture);
	picture.setOrigin(picture.getGlobalBounds().width / 2, picture.getGlobalBounds().height / 2);
	picture.setPosition(_position);
	picture.setRotation(_rotation);
}

bool Rocket::checkCollision(vector<Monster> & monsters, int & cash, int & kills)
{
	for (unsigned j = 0; j < monsters.size(); j++)
	{
		if (picture.getGlobalBounds().contains(monsters[j].picture.getPosition()))
		{
			if (monsters[j].hurt(getDamage()))
			{
				kills++;
				cash += monsters[j].getLevel();
				monsters.erase(monsters.begin() + j);
				j--;
				numberOfMonster = -1;
			}
			return true;
		}
	}
	return false;
}

int Rocket::getDamage()
{
	return damage;
}

void Rocket::display(sf::RenderWindow & window)
{
	window.draw(picture);
}
