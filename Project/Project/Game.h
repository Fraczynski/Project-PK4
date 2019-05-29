#pragma once
#include "Monster.h"
#include "Rocket1.h"
#include "Rocket2.h"
#include "Rocket3.h"
#include "Map.h"
#include "GUI.h"
#include "Menu.h"

using namespace std;

class Game
{
	GUI gui;				//obiekt wyswietlajacy gre
	Menu menu;
	int roundTime = 1200;	//czas pojedynczej rundy
	int timeToNextRound;	//pozostaly czas do kolejnej rundy
	int ifMovingTurret;		//czy przenoszona aktualnie jest wiezyczka: 0 - nie; 1 - tak
	int clicked;			//numer zaznaczonej wiezyczki: -1 - brak zaznaczonej
	int level;				//numer aktualnego poziomu
	int cash;				//poczatkowa ilosc pieniedzy
	int kills;				//licznik zabitych potworow
	int monsterSize = 40;	//rozmiar obrazka potwora
	int monsterPictureX;	//wspolrzedna x aktualnego sprite'a potwora
	int monsterPictureY;	//wspolrzedna y aktualnego sprite'a potwora
	Vector2i mousePosition;	//zmienna do przechowywania wspolrzednych pozycji myszy
	Vector2i vectorTurret1 = Vector2i(38, 670);		//pozycja wiezyczek w sklepie
	Vector2i vectorTurret2 = Vector2i(200, 670);
	Vector2i vectorTurret3 = Vector2i(360, 670);
	unique_ptr <Turret> turret1;	//wiezyczki w sklepie bedace wzorcami dla budowanych wiezyczek
	unique_ptr <Turret> turret2;
	unique_ptr <Turret> turret3;
	vector<Map> mapCorners;		//wspolrzedne (w ktorych potwory musza zmienic kierunek) i kierunki
	vector<Monster> monsters;	//wektor potworow
	vector<Turret> turrets;		//wektor wiezyczek
	vector<unique_ptr<Rocket>> rockets;		//wektor wskaznikow na rakiety

public:
	Game();
	void guiMethods();
	void menuMethods();
	void events();				//obsluga zdarzen
	bool isPlayed();
	void resetGame();			//restartowanie gry
	void resetTurrets();		//przywracanie wzorcowych wiezyczek do sklepu
	void pause();				//wstrzymanie gry
	bool pauseEvents();			//obsluga zdarzen w menu
	void leftButtonReleased();	//sprawdzanie polozenia wskaznika myszy podczas puszczenia lewego przycisku
	void movingTurret();		//upuszczanie wiezyczki w celu jej wybudowania
	void moveTurret();			//przenoszenie wiezyczek
	bool notMovingTurret();		//sprawdzanie, czy rozpoczeto przenoszenie wiezyczki w celu jej wybudowania
	bool turretClicked();		//wyswietlanie informacji o zaznaczonej wiezyczce
	void upgradeTurrets();		//ulepszanie wiezyczek
	void move_monsters();		//przemieszczanie wszystkich potworow
	void add_monsters();		//dodawanie potworow
	void rotate_turrets();		//obracanie wiezyczek
	void move_missiles();		//przemieszczanie pociskow
	bool checkPlace(const Vector2f & position, const int & w, const int & h);		//sprawdzanie miejsca podczas proby wybudowania wiezyczki
	void save();			//zapis do pliku
	void load();			//odczyt z pliku
	void shoot();			//wystrzeliwanie pociskow
};