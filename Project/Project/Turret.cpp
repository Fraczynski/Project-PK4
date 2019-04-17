#include "Turret.h"
#include <string.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Rest.h"

using namespace std;
using namespace sf;

Turret::Turret(int _id, int _price, int _damage, int _rate, int _range, Texture & _picture, Vector2f _position) : id(_id), price(_price), damage(_damage), rate(_rate), range(_range)
{
	picture.setTexture(_picture);
	picture.setPosition(_position);
	if (id == 2)
		picture.setOrigin(picture.getGlobalBounds().width / 2, picture.getGlobalBounds().height / 1.8);
	else
		picture.setOrigin(picture.getGlobalBounds().width / 2, picture.getGlobalBounds().height / 2);
	/*qDamage.push(Upgrading(0, 0));
	qRange.push(Upgrading(0, 0));
	qRate.push(Upgrading(0, 0));*/
	switch (_id)
	{
	case 0:
		upgradingTurret(id, qDamage, qRange, qRate);
		break;
	case 1:
		upgradingTurret(id, qDamage, qRange, qRate);
		break;
	case 2:
		upgradingTurret(id, qDamage, qRange, qRate);
		break;
	}
}

Turret::Turret(const Turret & _turret) : id(_turret.id),  damage(_turret.damage), rate(_turret.rate), range(_turret.range)
{
	picture.setTexture(*(_turret.picture.getTexture()));
	picture.setPosition(_turret.picture.getPosition());
	picture.setOrigin(_turret.picture.getOrigin());
	switch (id)
	{
	case 0:
		upgradingTurret(id, qDamage, qRange, qRate);
		break;
	case 1:
		upgradingTurret(id, qDamage, qRange, qRate);
		break;
	case 2:
		upgradingTurret(id, qDamage, qRange, qRate);
		break;
	}
}

int Turret::getPrice()
{
	return price;
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

void Turret::upgrade(int upgrading, int & cash)			//poprawic ceny
{
	switch (upgrading)
	{
	case 0:
		if (cash - qDamage.front().getPrice() >= 0 && qDamage.size() > 1)
		{
			cash -= qDamage.front().getPrice();
			damage = qDamage.front().getValue();
			qDamage.pop();
		}
		break;
	case 1:
		if (cash - qRange.front().getPrice() >= 0 && qRange.size() > 1)
		{
			cash -= qRange.front().getPrice();
			range = qRange.front().getValue();
			qRange.pop();
		}
		break;
	case 2:
		if (cash - qRate.front().getPrice() >= 0 && qRate.size() > 1)
		{
			cash -= qRate.front().getPrice();
			rate = qRate.front().getValue();
			qRate.pop();
		}
		break;
	}
}
