#include "Rocket.h"
#include "Rocket3.h"
#include <string.h>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

Rocket3::Rocket3(int _speed, int _damage, int _rotation, int _timeOfLife, int _numberOfMonster, Texture & _picture, Vector2f _position) :
				Rocket(_speed, _damage, _rotation, _numberOfMonster, _picture, _position), timeOfLife(_timeOfLife)
{
	picture.setOrigin(_picture.getSize().x / 2 , _picture.getSize().y);
}

bool Rocket3::specialAbilities(vector<Monster> & monsters, int & cash, int & kills)
{
	if (--timeOfLife <= 0)
	{
		return true;
	}
	else if (monsters.empty() || monsters.begin()->picture.getPosition().y < 0)
	{
		return true;
	}
	else if (numberOfMonster < monsters.size() && numberOfMonster >= 0)
	{
		checkCollision(monsters, cash, kills);
		return false;
	}
	return false;
}
