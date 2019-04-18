#pragma once
#include <vector>
#include <queue>
#include "Monster.h"

class Upgrading			//klasa przechowujaca pare liczb - cene i wartosc ulepszenia
{
	int price;			//cena ulepszenia
	int value;			//wartosc ulepszenia

public:
	Upgrading(int _price, int _value);		//konstruktor przypisujacy wartosci zmiennym
	int getPrice();			//pobieranie ceny ulepszenia
	int getValue();			//pobieranie wartosci ulepszenia
};

class Turret			//klasa reprezentujaca wiezyczke
{
public:
	int id;				//unikalny numer
	int price;			//cena zakupu
	int timeToShoot = 0;		//pozostaly czas do kolejnego wystrzalu
	int rotationSpeed = 2;		//max predkosc obracania podczas celowania
	int damage;			//zadawane obrazenia
	int range;			//zasieg
	int rate;			//czestotliwosc strzelania
	int aimAtMonster = -1;			//numer potwora, na ktory wycelowala wiezyczka
	sf::Sprite picture;			//obrazek wiezyczki
	std::queue<Upgrading> qDamage;		//kolejka z zawartoscia kolejnych ulepszen zadawanych obrazen
	std::queue<Upgrading> qRange;		//kolejka z zawartoscia kolejnych ulepszen zasiegu
	std::queue<Upgrading> qRate;		//kolejka z zawartoscia kolejnych ulepszen czestotliwosci strzelania

	Turret(int _id, sf::Texture & _picture, sf::Vector2f _position);			//konstruktor tworzacy wiezyczke (uzywany dla wiezyczek w menu)
	Turret(const Turret & _turret);					//konstruktor tworzacy kopie wiezyczki (uzywany przy budowaniu wiezyczki na mapie - kopia danej wiezyczki z menu)
	void upgradingTurret();				//wypelnianie kolejek wartosciami kolejnych ulepszen wraz z ich cenami
	int getPrice();						//pobieranie ceny wiezyczki
	void rotate(const std::vector<Monster> &);			//obracanie wiezyczki w strone odpowiedniego potwora
	int shoot(std::vector<Monster> &);				//strzelanie do odpowiedniego potwora
	bool isInRange(const Monster &);				//sprawdzanie czy dany potwor jest w zasiegu wiezyczki
	void upgrade(int upgrading, int & cash);		//ulepszanie danej cechy wiezyczki
};