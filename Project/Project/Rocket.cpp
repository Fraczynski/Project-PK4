#include "Rocket.h"
#include <string.h>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

Rocket::Rocket(int _speed, int _damage, int _rotation, int _rotationSpeed, int _numberOfMonster, Texture & _picture, Vector2f _position) : 
			   speed(_speed), damage(_damage), rotationSpeed(_rotationSpeed), numberOfMonster(_numberOfMonster)
{
	picture.setTexture(_picture);
	picture.setOrigin(picture.getGlobalBounds().width / 2, picture.getGlobalBounds().height / 2);
	picture.setPosition(_position);
	picture.setRotation(_rotation);
}

bool Rocket::move(vector<Monster> & monsters, int & cash, int & kills)
{
	if (monsters.empty() || monsters.begin()->picture.getPosition().y < 0)
	{
		picture.rotate(3);
		picture.move(sin((picture.getRotation()) * ((atan(1) * 4) / 180)) * speed, -cos((picture.getRotation()) * ((atan(1) * 4) / 180)) * speed);
	}
	else if(numberOfMonster < monsters.size() && numberOfMonster >= 0)
	{
		picture.setRotation(atan2(monsters[numberOfMonster].picture.getPosition().y - picture.getPosition().y,
			monsters[numberOfMonster].picture.getPosition().x - picture.getPosition().x) * (180 / (atan(1) * 4)) + 90);
		picture.move(sin((picture.getRotation()) * ((atan(1) * 4) / 180)) * speed, -cos((picture.getRotation()) * ((atan(1) * 4) / 180)) * speed);

		return checkCollision(monsters, cash, kills);
	}
	else
	{
		numberOfMonster = -1;
		picture.setRotation(atan2(monsters.begin()->picture.getPosition().y - picture.getPosition().y,
			monsters.begin()->picture.getPosition().x - picture.getPosition().x) * (180 / (atan(1) * 4)) + 90);
		picture.move(sin((picture.getRotation()) * ((atan(1) * 4) / 180)) * speed, -cos((picture.getRotation()) * ((atan(1) * 4) / 180)) * speed);

		return checkCollision(monsters, cash, kills);
	}
	return false;
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
