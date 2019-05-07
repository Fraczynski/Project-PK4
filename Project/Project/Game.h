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
	//GUI
	int width = 1000;			//szerokosc okna
	int height = 703;			//wysokosc okna
	RenderWindow window;		//okno aplikacji
	Vector2i mousePosition;		//zmienna do przechowywania wspolrzednych pozycji myszy
	Image I_map;				//obraz do sprawdzania kolorow pikseli mapy
	Texture T_background;		//tlo
	Texture T_background1;		//tlo mapy 1
	Texture T_background2;		//tlo mapy 2
	Texture T_map1;				//mapa 1
	Texture T_map2;				//mapa 2
	Texture T_bar;				//dolny pasek menu
	Texture T_arrow;			//wskazówka zegara
	Texture T_line;				//linie skreslajace stickman'ow, gry potwory dotra do bazy
	Texture T_gameOver;			//grafika konca gry
	Texture T_screenShot;		//zrzut ekranu podczas wyswietlania konca gry
	Sprite* background;			//wskaznik na tlo do wybranej przez uzytkownika mapy
	Sprite menuBackground;		//tlo menu
	Sprite background1;			//tlo mapy 1
	Sprite background2;			//tlo mapy 2
	Sprite screenShot;			//zrzut ekranu podczas wyswietlania konca gry
	Sprite bar;					//dolny pasek menu
	Sprite arrow;				//wskazówka zegara
	Sprite gameOver;			//grafika konca gry
	CircleShape circle;			//kolo pokazujace zasieg wiezyczki po jej zaznaczeniu
	Sprite* map;				//wskaznik na wybrana przez uzytkownika mape
	Sprite map1;				//mapa 1
	Sprite map2;				//mapa 2
	Texture T_button;			//tekstura przycisku
	Texture T_buttonSmall;			//tekstura malego przycisku
	unique_ptr<Button> buttonResume;	//przycisk resume
	unique_ptr<Button> buttonRestart;	//przycisk restart
	unique_ptr<Button> buttonSave;		//przycisk save
	unique_ptr<Button> buttonLoad;		//przycisk save
	unique_ptr<Button> buttonExit;		//przycisk exit
	unique_ptr<Button> buttonMap1;		//przycisk wybierania mapy 1
	unique_ptr<Button> buttonMap2;		//przycisk wybierania mapy 2
	unique_ptr<Button> buttonUpgradingDamage;
	unique_ptr<Button> buttonUpgradingRange;
	unique_ptr<Button> buttonUpgradingRate;

	Texture T_turret1;				//tekstury wie¿yczek
	Texture T_turret2;
	Texture T_turret3;
	Texture T_monster;				//tekstura potwora
	Texture T_missile1;				//tekstury pociskow
	Texture T_missile2;
	Texture T_missile3;
	Texture T_cursor1;				//tekstura zwyklego wskaznika
	Texture T_cursor2;				//tekstura wskaznika podczas przenoszenia wiezyczki
	Sprite cursor;					//obrazek aktualnego kursora
	Font fontCalibri;				//czcionka calibri
	Font fontTimesNewRoman;			//czcionka times new roman
	vector<Map> mapCorners;			//wspolrzedne (w ktorych potwory musza zmienic kierunek) i kierunki
	Vector2f* endLinesMap;			//wskaznik na wspolrzedne koncowych linii dla mapy wybranej przez uzytkownika
	Vector2f endLinesMap1 = Vector2f(343, 272);		//wspolrzedne koncowych linii dla mapy 1
	Vector2f endLinesMap2 = Vector2f(25, 580);		//wspolrzedne koncowych linii dla mapy 1
	Vector2f vectorTurret1 = Vector2f(38, 670);			//pozycja wiezyczek w sklepie
	Vector2f vectorTurret2 = Vector2f(200, 670);
	Vector2f vectorTurret3 = Vector2f(360, 670);
	unique_ptr <Turret> turret1;		//wiezyczki w sklepie bedace wzorcami dla budowanych wiezyczek
	unique_ptr <Turret> turret2;
	unique_ptr <Turret> turret3;
	unique_ptr <Texts> texts;			//obiekt zawierajacy wszystkie wypisywane teksty

	//logika gry
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
	vector<Monster> monsters;	//wektor potworow
	vector<Turret> turrets;		//wektor wiezyczek
	vector<unique_ptr<Rocket>> rockets;		//wektor wskaznikow na rakiety
	vector<Sprite> lines;		//wektor lini skreslajacych stickman'ow

public:
	//logika gry
	void menu();
	bool menuEvents();
	bool isPlayed();
	void resetGame();			//restartowanie gry
	void resetTurrets();		//przywracanie wzorcowych wiezyczek do sklepu
	void events();				//obsluga zdarzen
	void pause();				//wstrzymanie gry
	bool pauseEvents();			//obsluga zdarzen w menu
	void leftButtonReleased();	//sprawdzanie polozenia wskaznika myszy podczas puszczenia lewego przycisku
	void movingTurret();		//upuszczanie wiezyczki w celu jej wybudowania
	void moveTurret();			//przenoszenie wiezyczek
	bool notMovingTurret();		//sprawdzanie, czy rozpoczeto przenoszenie wiezyczki w celu jej wybudowania
	bool turretClicked();		//wyswietlanie informacji o zaznaczonej wiezyczce
	void upgradeTurrets();		//ulepszanie wiezyczek
	void updateCircle(const Vector2f & position, const int & range);		//aktualizacja kola okreslajacego zasieg danej wiezyczki
	void updateClock();			//aktualizacja zegara informujacego o czasie rundy
	void move_monsters();		//przemieszczanie wszystkich potworow
	void add_monsters();		//dodawanie potworow
	void rotate_turrets();		//obracanie wiezyczek
	void move_missiles();		//przemieszczanie pociskow
	bool checkPlace(const Vector2f & position, const int & w, const int & h);		//sprawdzanie miejsca podczas proby wybudowania wiezyczki
	bool checkPixel(const int & x, const int & y);		//sprawdzanie czy piksel o danych wspolrzednych jest koloru sciezki potworow
	void addLines();	//przekreslanie stickman'ow
	void save();		//zapis do pliku
	void load();		//odczyt z pliku
	void shoot();		//wystrzeliwanie pociskow
	void end();	//koniec gry jesli potworki dotarly do bazy
	//bool end();			//koniec gry

	//GUI
	void loadGraphics();
	void display();
	void pauseDisplay(const Sprite & cursorTmp);
	bool endAnimation();
	void checkCorners();
};