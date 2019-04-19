#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include "Map.h"

class Monster			//klasa przechowujaca informacjê o potworze
{
	int HP;				//ilosc pozostalego zycia
	int level;			//numer rundy = poczatkowa ilosc zycia
	float speed = 1;		//predkosc poruszania sie
	int direction = 0;		//kierunek przemieszczania sie
	sf::Text hp;			//wyswietlany tekst nad potworem z iloscia pozostalego zycia
	sf::Sprite picture;		//obrazek potwora

public:
	Monster(const int _level, const sf::Font & font, const sf::Texture & _picture, const sf::Vector2f _position, const int & _monsterPictureX, const int & _monsterPictureY, const int & _monsterSize);		//konstruktor tworzacy potwora
	int move(const Map map[]);					//przemieszczanie potwora
	bool hurt(const int damage);				//odejmowanie zycia
	void display(sf::RenderWindow & window);	//wyswietlanie potwora
	int getLevel();								//pobieranie poczatkowej ilosci zycia
	sf::Vector2f getPosition();					//pobieranie pozycji sprite'a
	void save(std::fstream & file);				//zapis stanu obiektu do pliku
	void loadParameters(const int & _direction, const int & _HP);		//ladowanie parametrow obiektu, podczas odczytu z pliku, ktorych nie obejmuje konstruktor
};

