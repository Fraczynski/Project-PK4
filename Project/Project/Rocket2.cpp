#include "Rocket.h"
#include "Rocket2.h"
#include <string.h>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

Rocket2::Rocket2(int _speed, int _damage, int _rotation, int _numberOfMonster, Texture & _picture, Vector2f _position) : 
				Rocket(_speed, _damage, _rotation, _numberOfMonster, _picture, _position)
{
	
}

bool Rocket2::specialAbilities(vector<Monster> & monsters, int & cash, int & kills)
{
	picture.move(sin((picture.getRotation()) * ((atan(1) * 4) / 180)) * speed, -cos((picture.getRotation()) * ((atan(1) * 4) / 180)) * speed);
	if (monsters.empty() || monsters.begin()->picture.getPosition().y < 0)
	{
		return false;
	}
	else if(numberOfMonster < monsters.size() && numberOfMonster >= 0)
	{
		return checkCollision(monsters, cash, kills);
	}
	return false;
}
	