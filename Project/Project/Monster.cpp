#include "Monster.h"
#include <string.h>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

Monster::Monster(const int _level, const Font & font, const Texture & _picture, const Vector2f _position, const int & _monsterPictureX, const int & _monsterPictureY, 
				 const int & _monsterSize) : Picture(_picture, _position, _monsterPictureX, _monsterPictureY, _monsterSize), HP(_level), level(_level)		//konstruktor tworzacy potwora
{
	hp.setFont(font);
	hp.setCharacterSize(16);
	hp.setFillColor(Color::White);
	hp.setString(to_string(HP));
	hp.setOrigin(hp.getGlobalBounds().width / 2, hp.getGlobalBounds().height / 2);
}

int Monster::move(const list<Map> & mapCorners)			//przemieszczanie potwora
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
	for (auto it = mapCorners.begin(); it != mapCorners.end(); ++it)		//sprawdzanie, czy nalezy zmienic kierunek poruszania sie
	{
		if (picture.getPosition() == it->position)
		{
			direction = it->newDirection;
			break;
		}
	}
	if (direction == mapCorners.back().newDirection)		//sprawdzanie, czy potwor dotarl do konca sciezki
	{
		return 1;
	}
	hp.setPosition(picture.getPosition().x, picture.getPosition().y - picture.getGlobalBounds().height / 2 - 12);		//aktualizacja pozycji tekstu z iloscia pozostalego zycia
	return 0;
}

bool Monster::hurt(const int & damage)		//odejmowanie zycia
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

Vector2f Monster::getPosition()
{
	return picture.getPosition();
}

void Monster::save(fstream & file)						//zapis stanu obiektu do pliku
{
	file << level << " " << (int)picture.getPosition().x << " " << (int)picture.getPosition().y << " " << picture.getTextureRect().left << " " << picture.getTextureRect().top << " ";
	file << picture.getTextureRect().width << " " << direction << " " << HP << endl;
}

void Monster::loadParameters(const int & _direction, const int & _HP)				//ladowanie parametrow obiektu, podczas odczytu z pliku, ktorych nie obejmuje konstruktor
{
	direction = _direction;
	HP = _HP;
}
