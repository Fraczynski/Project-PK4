#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Monster.h"

class Rocket		//klasa abstrakcyjna reprezentuj¹ca pocisk
{
public:
	int speed;		//predkosc pocisku
	int damage;		//ilosc zadawanych obrazen
	int numberOfMonster;	//numer potwora, na ktory zostal wycelowany pocisk
	sf::Sprite picture;		//obrazek pocisku

public:
	Rocket(int _speed, int _damage, int _rotation, int _numberOfMonster, sf::Texture & _picture, sf::Vector2f _position);		//konstruktor tworzacy pocisk
	virtual bool specialAbilities(std::vector<Monster> & monsters, int & cash, int & kills) = 0;		//specjalne zdolnosci danego typu pocisku
	bool checkCollision(std::vector<Monster> & monsters, int & cash, int & kills);			//sprawdzanie wyst¹pienia kolizji z potworem
	int getDamage();					//pobieranie ilosci zadawanych obrazen
	void display(sf::RenderWindow & window);		//wyswietlanie pocisku
};