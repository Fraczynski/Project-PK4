#pragma once
#include <SFML/Graphics.hpp>
#include "Turret.h"
#include "Monster.h"

class Texts
{
	sf::Text text[21];						//tabela tekstow: 0 - damage, 1 - range, 2 - rate, 3 - upgrading damage, 4 - upgrading  range, 5 - upgrading rate, 
											//6 - price1, 7 - price2, 8 - price3, 9 - cash, 10 - kills, 11 - waves, 12 - damage turret1, 13 - range turret1, 14 - rate turret1,
											//15 - damage turret2, 16 - range turret2, 17 - rate turret2, 18 - damage turret3, 19 - range turret3, 20 - rate turret3
	sf::Color bright = sf::Color(255, 255, 255);		//kolor podswietlonych informacji
	sf::Color dark = sf::Color(90, 90, 90);				//kolor przygaszonych informacji

public:
	Texts(const sf::Font & font, const sf::Vector2f & vectorTurret1, const sf::Vector2f & vectorTurret2, const sf::Vector2f & vectorTurret3, Turret *turret1, Turret *turret2, Turret *turret3);	//konstruktor tworzacy teksty
	
	void updateInfo(Turret & turret);		//wyswietlanie informacji o wiezyczce (przenoszonej lub klikniêtej)

	void updateInfo();		//przyciemnianie informacji o wiezyczce (zadna nie jest klikniêta)

	void updateStats(const int & cash, const int & kills, const int & level);		//aktualizowanie tekstu zawierajacego statystyki gry

	void display(const int & cash, const int & kills, const int & level, sf::RenderWindow & window);			//wyswietlanie tekstów

	int upgradingTextClicked(sf::RenderWindow & window);			//sprawdzanie, czy kliknieto przycisk ulepszania o podanym numerze
};

