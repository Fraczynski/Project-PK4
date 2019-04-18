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

using namespace sf;
using namespace std;

class Game
{
	int width = 1000;			//szerokosc okna
	int height = 703;			//wysokosc okna
	int timeToNextRound;		//pozostaly czas do kolejnej rundy
	int roundTime;			//czas pojedynczej rundy
	int ifMovingTurret;			//czy przenoszona aktualnie jest wiezyczka: 0 - nie; 1 - tak
	int clicked;				//numer zaznaczonej wiezyczki: -1 - brak zaznaczonej
	int level;					//numer aktualnego poziomu
	int cash;				//poczatkowa ilosc pieniedzy											//zmienic po testach
	int kills;					//licznik zabitych potworow
	RenderWindow window;			//okno aplikacji
	Vector2i mousePosition;			//zmienna do przechowywania wspolrzednych pozycji myszy
	Image I_map1;					//obraz do sprawdzania kolorow pikseli mapy
	Texture T_background;			//tlo
	Texture T_map1;					//mapa
	Texture T_bar;					//dolny pasek menu
	Texture T_arrow;				//wskazówka zegara
	Texture T_line;					//linie skreslajace stickman'ow, gry potwory dotra do bazy
	Texture T_gameOver;				//grafika konca gry
	Texture T_screenShot;			//zrzut ekranu podczas wyswietlania konca gry
	Sprite background;				//tlo
	Sprite screenShot;				//zrzut ekranu podczas wyswietlania konca gry
	Sprite bar;						//dolny pasek menu
	Sprite arrow;					//wskazówka zegara
	Sprite gameOver;				//grafika konca gry
	CircleShape circle;				//kolo pokazujace zasieg wiezyczki po jej zaznaczeniu
	Texture T_buttonResume;			//przycisk resume
	Texture T_buttonRestart;		//przycisk restart
	Texture T_buttonExit;			//przycisk exit
	Sprite buttonResume;			//przycisk resume
	Sprite buttonRestart;			//przycisk restart
	Sprite buttonExit;				//przycisk exit
	const Map cornersMap1[11] = { {Vector2f(920, 539), 1}, {Vector2f(83, 539), 2}, {Vector2f(83, 83), 3}, {Vector2f(815, 83), 0}, {Vector2f(815, 431), 1}, {Vector2f(190, 431), 2 }, 
					 {Vector2f(190, 188), 3}, {Vector2f(709, 188), 0}, {Vector2f(709, 323), 1}, {Vector2f(450, 323), 2}, { Vector2f(450, 295), 5 } };		//wspolrzedne (w ktorych potwory musza zmienic kierunek) i kierunki
	Texture T_turret1;				//tekstury wie¿yczek
	Texture T_turret2;
	Texture T_turret3;
	Texture T_monster1;				//tekstury potworkow
	Texture T_monster2;
	Texture T_missile1;				//tekstury pociskow
	Texture T_missile2;
	Texture T_missile3;
	Texture T_cursor1;				//tekstura zwyklego wskaznika
	Texture T_cursor2;				//tekstura wskaznika podczas przenoszenia wiezyczki
	Sprite cursor;					//obrazek aktualnego kursora
	Sprite map1;					//mapa
	Turret *turret1;				//wiezyczki w sklepie bedace wzorcami dla budowanych wiezyczek
	Turret *turret2;
	Turret *turret3;
	Vector2f vectorTurret1 = Vector2f(38, 670);			//pozycja wiezyczek w sklepie
	Vector2f vectorTurret2 = Vector2f(200, 670);
	Vector2f vectorTurret3 = Vector2f(360, 670);

	Font font;					//czcionka
	Texts *texts;
	
	vector<Monster> monsters;		//wektor potworow
	vector<Turret> turrets;			//wektor wiezyczek
	vector<Rocket *> rockets;		//wektor wskaznikow na rakiety
	vector<Sprite> lines;			//wektor lini skreslajacych stickman'ow


public:
	void gameLoop();		//glowna petla gry

	void loadGraphics();		//wczytywanie grafik i ich odpowiednie ustawienia

	void resetGame();			//restartowanie gry

	void resetTurrets();		//przywracanie wzorcowych wiezyczek do sklepu

	void events();			//obsluga zdarzen

	void pause();			//wstrzymanie gry

	bool buttonEvent();

	void leftButtonReleased();		//sprawdzanie polozenia wskaznika myszy podczas puszczenia lewego przycisku

	void movingTurret();		//upuszczanie wiezyczki w celu jej wybudowania

	void moveTurret();

	bool notMovingTurret();		//sprawdzanie, czy rozpoczeto przenoszenie wiezyczki w celu jej wybudowania

	bool turretClicked();		//wyswietlanie informacji o zaznaczonej wiezyczce

	void upgradeTurrets();		//ulepszanie wiezyczek

	void updateCircle(const Vector2f & position, const int & range);		//aktualizacja kola okreslajacego zasieg danej wiezyczki

	void display();			//wyswietlanie wszystkich grafik

	void updateClock();		//aktualizacja zegara informujacego o czasie rundy

	void move_monsters();		//przemieszczanie wszystkich potworow

	void add_monsters(int);		//dodawanie potworow

	void rotate_turrets();		//obracanie wiezyczek

	void move_missiles();		//przemieszczanie pociskow

	bool checkPlace(Vector2f, int, int);		//sprawdzanie miejsca podczas proby wybudowania wiezyczki

	bool checkPixel(int x, int y);		//sprawdzanie czy piksel o danych wspolrzednych jest koloru sciezki potworow

	void shoot();			//wystrzeliwanie pociskow

	void end();			//animacja konca gry

	void cleaner();		//zwalnianie zasobow
};