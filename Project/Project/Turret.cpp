#include "Turret.h"
#include <string.h>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

Turret::Turret(int _id, int _damage, int _rate, int _range, Texture & _picture, Vector2f _position) : id(_id), damage(_damage), rate(_rate), range(_range)
{
	picture.setTexture(_picture);
	picture.setOrigin(picture.getGlobalBounds().width / 2, picture.getGlobalBounds().height / 2);
	picture.setPosition(_position);
}

void Turret::rotate(const vector<Monster> & monsters)
{
	for (unsigned i = 0; i < monsters.size(); i++)
	{
		if (isInRange(monsters[i]))
		{
			picture.setRotation(atan2(monsters[i].picture.getPosition().y - picture.getPosition().y,
				monsters[i].picture.getPosition().x - picture.getPosition().x) * (180 / (atan(1) * 4)) + 90);
			aimAtMonster = i;
			return;
		}
	}
	aimAtMonster = -1;
	/*
	//double angle = (360 - (double)((int)(270 - ((atan2(monsters.begin()->picture.getPosition().y - i->picture.getPosition().y, 
						monsters.begin()->picture.getPosition().x - i->picture.getPosition().x)) * (180 / (atan(1) * 4)))) % 360) - i->picture.getRotation());
	//i->picture.rotate(360 - (270 - (atan2(monsters.begin()->picture.getPosition().y - i->picture.getPosition().y, 
						monsters.begin()->picture.getPosition().x - i->picture.getPosition().x)) * (180 / (atan(1) * 4))) - i->picture.getRotation());

	if (angle > 1 && angle <= 180)
	{
		i->picture.rotate(angle / 20);
	}
	else if (angle > 180 || angle < -1)
	{
		i->picture.rotate(-(360 - angle) % 180 / 20);
	}
	else
	{
		i->picture.rotate(angle);
	}*/
}

int Turret::shoot(vector<Monster> & monsters)
{
	if (timeToShoot > 0)
	{
		timeToShoot--;
		return -1;
	}
	else
	{
		if (aimAtMonster >= 0 && aimAtMonster < monsters.size())
		{
			timeToShoot = rate;
			return aimAtMonster;
		}
	}
}

bool Turret::isInRange(const Monster & m)
{
	if (sqrt(pow(m.picture.getPosition().x - picture.getPosition().x, 2) + pow(m.picture.getPosition().y - picture.getPosition().y, 2)) < range)
	{
		return true;
	}
	return false;
}
