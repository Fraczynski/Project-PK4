#pragma once
#include <SFML/Graphics.hpp>
#include "Monster.h"
#include "Turret.h"
#include "Rocket.h"
#include "Rocket1.h"
#include "Rocket2.h"
#include "Rocket3.h"
#include "Map.h"
#include "Texts.h"
#include "Icon.h"
#include "GUI.h"


using namespace sf;
using namespace std;

class Game : public GUI
{
	int roundTime = 1200;		//czas pojedynczej rundy
	int timeToNextRound;		//pozostaly czas do kolejnej rundy
	int ifMovingTurret;			//czy przenoszona aktualnie jest wiezyczka: 0 - nie; 1 - tak
	int clicked;				//numer zaznaczonej wiezyczki: -1 - brak zaznaczonej
	int level;					//numer aktualnego poziomu
	int cash;					//poczatkowa ilosc pieniedzy
	int kills;					//licznik zabitych potworow
	int monsterSize = 40;		//rozmiar obrazka potwora
	int monsterPictureX;		//wspolrzedna x aktualnego sprite'a potwora
	int monsterPictureY;		//wspolrzedna y aktualnego sprite'a potwora
	
	const Map cornersMap1[11] = { {Vector2f(920, 539), 1}, {Vector2f(83, 539), 2}, {Vector2f(83, 83), 3}, {Vector2f(815, 83), 0}, {Vector2f(815, 431), 1}, {Vector2f(190, 431), 2 }, 
					 {Vector2f(190, 188), 3}, {Vector2f(709, 188), 0}, {Vector2f(709, 323), 1}, {Vector2f(450, 323), 2}, { Vector2f(450, 295), 5 } };		//wspolrzedne (w ktorych potwory musza zmienic kierunek) i kierunki
	
	vector<Monster> monsters;		//wektor potworow
	vector<Turret> turrets;			//wektor wiezyczek
	vector<unique_ptr<Rocket>> rockets;		//wektor wskaznikow na rakiety
	vector<Sprite> lines;			//wektor lini skreslajacych stickman'ow

public:
	void gameLoop();		//glowna petla gry

private:
	void resetGame();			//restartowanie gry
	void resetTurrets();		//przywracanie wzorcowych wiezyczek do sklepu
	void events();			//obsluga zdarzen
	void pause();			//wstrzymanie gry
	bool buttonEvents();
	void leftButtonReleased();		//sprawdzanie polozenia wskaznika myszy podczas puszczenia lewego przycisku
	void movingTurret();		//upuszczanie wiezyczki w celu jej wybudowania
	void moveTurret();
	bool notMovingTurret();		//sprawdzanie, czy rozpoczeto przenoszenie wiezyczki w celu jej wybudowania
	bool turretClicked();		//wyswietlanie informacji o zaznaczonej wiezyczce
	void upgradeTurrets();		//ulepszanie wiezyczek
	void updateCircle(const Vector2f & position, const int & range);		//aktualizacja kola okreslajacego zasieg danej wiezyczki
	void updateClock();		//aktualizacja zegara informujacego o czasie rundy
	void move_monsters();		//przemieszczanie wszystkich potworow
	void add_monsters(int);		//dodawanie potworow
	void rotate_turrets();		//obracanie wiezyczek
	void move_missiles();		//przemieszczanie pociskow
	bool checkPlace(const Vector2f & position, const int & w, const int & h);		//sprawdzanie miejsca podczas proby wybudowania wiezyczki
	bool checkPixel(const int & x, const int & y);		//sprawdzanie czy piksel o danych wspolrzednych jest koloru sciezki potworow
	void addLines();	//przekreslanie stickman'ow
	void save();		//zapis do pliku
	void load();		//odczyt z pliku
	void shoot();		//wystrzeliwanie pociskow
	void end();
	void exit();		//zwalnianie zasobow
};