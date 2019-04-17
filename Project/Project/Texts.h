#pragma once
#include <SFML/Graphics.hpp>
#include "Monster.h"
#include <vector>
#include <queue>
#include "Turret.h"

class Texts
{
	sf::Text text[12];						//tabela tekstow: 0 - damage, 1 - range, 2 - rate, 3 - upgrading damage, 4 - upgrading  range, 5 - upgrading rate, 
											//6 - price1, 7 - price2, 8 - price3, 9 - cash, 10 - kills, 11 - waves
	sf::Color bright = sf::Color(255, 255, 255);
	sf::Color dark = sf::Color(90, 90, 90);

public:
	Texts(const sf::Font & font, sf::Vector2f vectorTurret1, sf::Vector2f vectorTurret2, sf::Vector2f vectorTurret3, Turret *turret1, Turret *turret2, Turret *turret3);
	
	void updateInfo(Turret & turret);		//wyswietlanie informacji o wiezyczce (przenoszonej lub klikniêtej)

	void updateInfo();		//przyciemnianie informacji o wiezyczce (zadna nie jest klikniêta)

	void updateStats(int & cash, int & kills, int & level);		//aktualizuje statystyki gry

	sf::Text & getText(int & i);

	bool upgradingTextClicked(sf::RenderWindow & window, const int & i);
};

