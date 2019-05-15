#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Turret.h"
#include "Texts.h"
#include "Icon.h"
#include "Rocket.h"

using namespace std;
using namespace sf;

class GUI
{
	int width = 1000;		//szerokosc okna
	int height = 703;		//wysokosc okna
	RenderWindow window;	//okno aplikacji
	Image I_map;			//obraz do sprawdzania kolorow pikseli mapy
	Texture T_background;	//tlo
	Texture T_background1;	//tlo mapy 1
	Texture T_background2;	//tlo mapy 2
	Texture T_map1;			//mapa 1
	Texture T_map2;			//mapa 2
	Texture T_bar;			//dolny pasek menu
	Texture T_arrow;		//wskazówka zegara
	Texture T_line;			//linie skreslajace stickman'ow, gry potwory dotra do bazy
	Texture T_gameOver;		//grafika konca gry
	Texture T_screenShot;	//zrzut ekranu podczas wyswietlania konca gry
	Sprite* background;		//wskaznik na tlo do wybranej przez uzytkownika mapy
	Sprite menuBackground;	//tlo menu
	Sprite background1;		//tlo mapy 1
	Sprite background2;		//tlo mapy 2
	Sprite screenShot;		//zrzut ekranu podczas wyswietlania konca gry
	Sprite bar;				//dolny pasek menu
	Sprite arrow;			//wskazówka zegara
	Sprite gameOver;		//grafika konca gry
	CircleShape circle;		//kolo pokazujace zasieg wiezyczki po jej zaznaczeniu
	Sprite* map;			//wskaznik na wybrana przez uzytkownika mape
	Sprite map1;			//mapa 1
	Sprite map2;			//mapa 2
	Texture T_button;		//tekstura przycisku
	Texture T_buttonSmall;	//tekstura malego przycisku
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

	Texture T_cursor1;				//tekstura zwyklego wskaznika
	Texture T_cursor2;				//tekstura wskaznika podczas przenoszenia wiezyczki
	Sprite cursor;					//obrazek aktualnego kursora
	Font fontTimesNewRoman;			//czcionka times new roman
	Vector2i mousePosition;		//zmienna do przechowywania wspolrzednych pozycji myszy
	const Texture * cursorPtr;
	Sprite cursorTmp;
	Vector2f* endLinesMap;			//wskaznik na wspolrzedne koncowych linii dla mapy wybranej przez uzytkownika
	Vector2i vectorTurret1 = Vector2i(38, 670);			//pozycja wiezyczek w sklepie
	Vector2i vectorTurret2 = Vector2i(200, 670);
	Vector2i vectorTurret3 = Vector2i(360, 670);
	Vector2f endLinesMap1 = Vector2f(343, 272);		//wspolrzedne koncowych linii dla mapy 1
	Vector2f endLinesMap2 = Vector2f(25, 580);		//wspolrzedne koncowych linii dla mapy 1
	unique_ptr <Texts> texts;			//obiekt zawierajacy wszystkie wypisywane teksty
	vector<Sprite> lines;		//wektor lini skreslajacych stickman'ow
public:
	Texture T_monster;				//tekstura potwora
	Font fontCalibri;				//czcionka calibri
	Texture T_missile1;				//tekstury pociskow
	Texture T_missile2;
	Texture T_missile3;
	Texture T_turret1;				//tekstury wie¿yczek
	Texture T_turret2;
	Texture T_turret3;

	void loadGraphics();
	void display(vector<Turret> & turrets, vector<Monster> & monsters, vector<unique_ptr<Rocket>> & rockets, const int & clicked, const int & cash, const int & kills,
		const int & level, int & timeToNextRound, Turret * turret1, Turret * turret2, Turret * turret3);
	Vector2i getMousePosition();	//pobieranie wspolrzednych kursora myszy
	void changeCursor(int cursorNumber);		//zmiana kursora myszy
	void updateInfo(Turret & turret);		//wyswietlanie informacji o wiezyczce (przenoszonej lub klikniêtej)
	void updateInfo();		//przyciemnianie informacji o wiezyczce (zadna nie jest klikniêta)
	void setTexts(Turret * turret1, Turret * turret2, Turret * turret3);
	void setMenuGraphics();
	void resetMenuGraphics();
	void displayMenu();
	void resetTurrets();
	bool pollEvent(Event & e);
	bool isButtonResumeClicked();
	bool isButtonRestartClicked();
	bool isButtonSaveClicked();
	bool isButtonLoadClicked();
	bool isButtonExitClicked();
	bool isButtonMapClicked();
	void linesClear();
	int selectedMap();
	int getLinesNumber();
	void takeScreenshot(vector<Turret> & turrets, vector<Monster> & monsters, vector<unique_ptr<Rocket>> & rockets, const int & clicked, const int & cash, const int & kills,
		const int & level, int & timeToNextRound, Turret * turret1, Turret * turret2, Turret * turret3);
	void restoreCursor();
	int upgradingTextClicked();
	int getHeight();
	int getWidth();
	void pauseDisplay();
	void endAnimation();
	void checkCorners(vector<Map> & mapCorners);
	bool checkPixel(const int & x, const int & y);						//sprawdzanie czy piksel o danych wspolrzednych jest koloru sciezki potworow
	void addLines();				//przekreslanie stickman'ow
	void updateCircle(const Vector2i & position, const int & range);	//aktualizacja kola okreslajacego zasieg danej wiezyczki
	void updateClock(const int & timeToNextRound);				//aktualizacja zegara informujacego o czasie rundy
	bool isOpen();
	void close();
};

