#include "Monster.h"
#include <string.h>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

Monster::Monster(int _level, Font & font, Texture & _picture, Vector2f _position) : HP(_level), level(_level)		//konstruktor tworzacy potwora
{
	picture.setTexture(_picture);
	picture.setOrigin(picture.getGlobalBounds().width / 2, picture.getGlobalBounds().height / 2);
	picture.setPosition(_position);

	hp.setFont(font);
	hp.setCharacterSize(16);
	hp.setFillColor(Color::White);
	//hp.setStyle(Text::Bold);
	hp.setString(to_string(HP));
	hp.setOrigin(hp.getGlobalBounds().width / 2, hp.getGlobalBounds().height / 2);
}

int Monster::move(const Map map[])			//przemieszczanie potwora
{
	switch (direction)			//sprawdzanie, w ktora strone przesunac potwora
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
	for (int j = 0; j <= 10; j++)		//sprawdzanie, czy nalezy zmienic kierunek poruszania sie
	{
		if (picture.getPosition() == map[j].position)
		{
			direction = map[j].newDirection;
			break;
		}
	}
	if (direction == map[10].newDirection)		//sprawdzanie, czy potwor dotarl do konca sciezki
	{
		return 1;
	}
	hp.setPosition(picture.getPosition().x, picture.getPosition().y - 27);		//aktualizacja pozycji tekstu z iloscia pozostalego zycia
	return 0;
}

bool Monster::hurt(int damage)		//odejmowanie zycia
{
	HP -= damage;
	hp.setString(to_string(HP));
	if (HP <= 0)
		return true;		//potwor umarl
	return false;		//potwor wciaz zyje
}

void Monster::display(RenderWindow & window)			//wyswietlanie potwora
{
	window.draw(picture);			//rysowanie obrazka potwora
	window.draw(hp);				//rysowanie ilosci pozostalego zycia
}

int Monster::getLevel()		//pobieranie poczatkowej ilosci zycia
{
	return level;
}
