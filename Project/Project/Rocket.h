#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include "Monster.h"

class Rocket		//klasa abstrakcyjna reprezentuj¹ca pocisk
{
protected:
	int id;			//numer rodzaju pocisku
	int speed;		//predkosc pocisku
	int damage;		//ilosc zadawanych obrazen
	int numberOfMonster;	//numer potwora, na ktory zostal wycelowany pocisk
	sf::Sprite picture;		//obrazek pocisku

public:
	Rocket(const int & _id, const int & _speed, const int & _damage, const int & _rotation, const int & _numberOfMonster, const sf::Texture & _picture, const sf::Vector2f _position);		//konstruktor tworzacy pocisk
	virtual bool specialAbilities(std::vector<Monster> & monsters, int & cash, int & kills) = 0;		//specjalne zdolnosci danego typu pocisku
	bool checkCollision(std::vector<Monster> & monsters, int & cash, int & kills);			//sprawdzanie wyst¹pienia kolizji z potworem
	int getDamage();					//pobieranie ilosci zadawanych obrazen
	void display(sf::RenderWindow & window);		//wyswietlanie pocisku
	void save(std::fstream & file);			//zapis informacji do pliku
};