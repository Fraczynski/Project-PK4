#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Texts.h"
#include "Rocket.h"

using namespace sf;
using namespace std;

class GUI
{
public:
	int width = 1000;				//szerokosc okna
	int height = 703;				//wysokosc okna
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
	Texture T_buttonSave;			//przycisk save
	Texture T_buttonLoad;			//przycisk save
	Texture T_buttonExit;			//przycisk exit
	Sprite buttonResume;			//przycisk resume
	Sprite buttonRestart;			//przycisk restart
	Sprite buttonSave;				//przycisk save
	Sprite buttonLoad;				//przycisk save
	Sprite buttonExit;				//przycisk exit
	Texture T_turret1;				//tekstury wie¿yczek
	Texture T_turret2;
	Texture T_turret3;
	Texture T_monster1;				//tekstura potwora
	Texture T_monster2;				//tekstura potwora
	Texture T_missile1;				//tekstury pociskow
	Texture T_missile2;
	Texture T_missile3;
	Texture T_cursor1;				//tekstura zwyklego wskaznika
	Texture T_cursor2;				//tekstura wskaznika podczas przenoszenia wiezyczki
	Sprite cursor;					//obrazek aktualnego kursora
	Sprite map1;					//mapa
	Font font;						//czcionka


	Vector2f vectorTurret1 = Vector2f(38, 670);			//pozycja wiezyczek w sklepie
	Vector2f vectorTurret2 = Vector2f(200, 670);
	Vector2f vectorTurret3 = Vector2f(360, 670);
	Turret *turret1;				//wiezyczki w sklepie bedace wzorcami dla budowanych wiezyczek
	Turret *turret2;
	Turret *turret3;
	Texts *texts;
public:
	
	void loadGraphics();

	void display(vector<Monster> & monsters, vector<Turret> & turrets, vector<Rocket *> & rockets, vector<Sprite> & lines, int & clicked, int & cash, int & kills, int & level, int & timeToNextRound);

	void pauseMenu(const Sprite & cursorTmp);

	bool endAnimation(vector<Sprite> & lines);
};

