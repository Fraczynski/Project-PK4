#include "Monster.h"
#include <string.h>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

Monster::Monster(int _level, Font & font, Texture & _picture, Vector2f _position) : HP(_level), level(_level)
{
	picture.setTexture(_picture);
	picture.setOrigin(picture.getGlobalBounds().width / 2, picture.getGlobalBounds().height / 2);
	picture.setPosition(_position);

	hp.setFont(font);
	hp.setCharacterSize(14);
	hp.setFillColor(Color(255, 105, 180));
	//hp.setStyle(Text::Bold);
	hp.setString(to_string(HP));
	hp.setOrigin(hp.getGlobalBounds().width / 2, hp.getGlobalBounds().height / 2);
}

int Monster::move(const Map map[])
{
	switch (direction)
	{
	case 0:
		picture.move(0, speed);
		break;
	case 1:
		picture.move(-speed, 0);
		break;
	case 2:
		picture.move(0, -speed);
		break;
	case 3:
		picture.move(speed, 0);
		break;
	}
	for (int j = 0; j <= 10; j++)
	{
		if (picture.getPosition() == map[j].position)
		{
			direction = map[j].changeDirectionTo;
			break;
		}
	}
	if (direction == map[10].changeDirectionTo)
	{
		return 1;
	}
	hp.setPosition(picture.getPosition().x, picture.getPosition().y - 27);
	return 0;
}

bool Monster::hurt(int damage)
{
	HP -= damage;
	hp.setString(to_string(HP));
	if (HP <= 0)
		return true;
	return false;
}

void Monster::display(RenderWindow & window)
{
	window.draw(picture);
	window.draw(hp);
}

int Monster::getLevel()
{
	return level;
}
