#pragma once
#include <vector>
#include <queue>
#include <fstream>
#include "Monster.h"

class Upgrading			//klasa przechowujaca pare liczb - cene i wartosc ulepszenia
{
	int price;			//cena ulepszenia
	int value;			//wartosc ulepszenia

public:
	Upgrading(const int _price, const int _value);		//konstruktor przypisujacy wartosci zmiennym
	int getPrice();			//pobieranie ceny ulepszenia
	int getValue();			//pobieranie wartosci ulepszenia
};

class Turret			//klasa reprezentujaca wiezyczke
{
	int id;				//unikalny numer
	int price = 0;			//cena zakupu
	int timeToShoot = 0;		//pozostaly czas do kolejnego wystrzalu
	int rotationSpeed = 2;		//max predkosc obracania podczas celowania
	int damage;			//zadawane obrazenia
	int range;			//zasieg
	int rate;			//czestotliwosc strzelania
	int aimAtMonster = -1;			//numer potwora, na ktory wycelowala wiezyczka
	std::queue<Upgrading> qDamage;		//kolejka z zawartoscia kolejnych ulepszen zadawanych obrazen
	std::queue<Upgrading> qRange;		//kolejka z zawartoscia kolejnych ulepszen zasiegu
	std::queue<Upgrading> qRate;		//kolejka z zawartoscia kolejnych ulepszen czestotliwosci strzelania
	sf::Sprite picture;			//obrazek wiezyczki

public:
	Turret(const int _id, const sf::Texture & _picture, const sf::Vector2f _position);			//konstruktor tworzacy wiezyczke (uzywany dla wiezyczek w menu)
	Turret(const Turret & _turret);					//konstruktor tworzacy kopie wiezyczki (uzywany przy budowaniu wiezyczki na mapie - kopia danej wiezyczki z menu)
	void loadParameters(const float & positionX, const float & positionY, const int & _timeToShoot, const int & _damage, const int & _range, const int & _rate,
		const int & _aimAtMonster, const float & rotation);				//ustawianie parametrow wiezyczki podczas odczytu z pliku, ktorych nie obejmuje konstruktor
	void upgradingTurret();				//wypelnianie kolejek wartosciami kolejnych ulepszen wraz z ich cenami
	int getID();					//pobieranie numeru ID wiezyczki
	int getPrice();					//pobieranie ceny wiezyczki
	int getDamage();				//pobeiranie wartosic zadawanych obrazen
	int getRange();					//pobieranie wartosci zasiegu
	int getRate();					//pobieranie wartosci czestotliwosci strzalow
	int getSize(int queue);			//pobieranie ilosci elementow danej kolejki
	int getFrontPrice(int queue);	//pobieranie ceny z pierwszego elementu danej kolejki
	void setPosition(const sf::Vector2f & vectorTurret);		//ustawianie sprite'a na podanej pozycji
	sf::Vector2f getPosition();				//pobieranie pozycji sprite'a
	int getWidth();					//pobieranie szerokosci sprite'a
	int getHeight();				//pobieranie wysokosci sprite'a
	bool contains(const sf::Vector2f & point);		//sprawdzenie, czy sprite wiezyczki zawiera podany punkt
	float getRotation();
	void rotate(std::vector<Monster> &);		//obracanie wiezyczki w strone odpowiedniego potwora
	int shoot(const std::vector<Monster> &);				//strzelanie do odpowiedniego potwora
	bool isInRange(Monster &);				//sprawdzanie czy dany potwor jest w zasiegu wiezyczki
	void upgrade(int upgrading, int & cash);		//ulepszanie danej cechy wiezyczki
	void display(sf::RenderWindow & window);		//wyswietlanie wiezyczki
	void save(std::fstream & file);					//zapis stanu wiezyczki do pliku
};