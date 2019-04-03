#include "Rocket.h"
#include "Rocket1.h"
#include <string.h>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

Rocket1::Rocket1(int _speed, int _damage, int _rotation, int _rotationSpeed, int _numberOfMonster, Texture & _picture, Vector2f _position) : 
				Rocket(_speed, _damage, _rotation, _numberOfMonster, _picture, _position), rotationSpeed(_rotationSpeed)
{

}

bool Rocket1::specialAbilities(vector<Monster> & monsters, int & cash, int & kills)
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