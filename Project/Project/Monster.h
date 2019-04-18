#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

class Monster			//klasa przechowujaca informacjê o potworze
{
public:
	int HP;				//ilosc pozostalego zycia
	int level;			//numer rundy = poczatkowa ilosc zycia
	float speed = 1;		//predkosc poruszania sie
	int direction = 0;		//kierunek przemieszczania sie
	sf::Text hp;			//wyswietlany tekst nad potworem z iloscia pozostalego zycia
	sf::Sprite picture;		//obrazek potwora

	Monster(int _level, sf::Font & font, sf::Texture & _picture, sf::Vector2f _position, int & _monsterPictureX, int & _monsterPictureY, int & _monsterSize);		//konstruktor tworzacy potwora
	int move(const Map map[]);		//przemieszczanie potwora
	bool hurt(int damage);				//odejmowanie zycia
	void display(sf::RenderWindow & window);		//wyswietlanie potwora
	int getLevel();				//pobieranie poczatkowej ilosci zycia
};

