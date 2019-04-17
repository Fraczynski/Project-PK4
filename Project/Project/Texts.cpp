#include <string.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Texts.h"

using namespace std;
using namespace sf;

Texts::Texts(const Font & font, Vector2f vectorTurret1, Vector2f vectorTurret2, Vector2f vectorTurret3, Turret *turret1, Turret *turret2, Turret *turret3)
{
	for (int i = 0; i < 12; i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(18);
		text[i].setOrigin(0, text[i].getGlobalBounds().height / 2);
	}
	text[0].setPosition(487, 627);
	text[1].setPosition(502, 649);
	text[2].setPosition(515, 671);
	text[3].setPosition(615, 627);
	text[4].setPosition(615, 649);
	text[5].setPosition(615, 671);
	text[6].setPosition(vectorTurret1.x - 33, vectorTurret1.y - 40);
	text[7].setPosition(vectorTurret2.x - 33, vectorTurret2.y - 40);
	text[8].setPosition(vectorTurret3.x - 33, vectorTurret3.y - 40);
	text[6].setString(to_string((*turret1).price) + "$");
	text[7].setString(to_string((*turret2).price) + "$");
	text[8].setString(to_string((*turret3).price) + "$");
	text[9].setPosition(756, 628);
	text[10].setPosition(764, 650);
	text[11].setPosition(752, 672);
}

void Texts::updateInfo(Turret & turret)
{
	text[0].setString("Damage  " + to_string(turret.damage));
	text[1].setString("Range  " + to_string(turret.range));
	text[2].setString("Rate  " + to_string(turret.rate));
	text[0].setFillColor(bright);
	text[1].setFillColor(bright);
	text[2].setFillColor(bright);
	if (turret.qDamage.size() > 1)
	{
		text[3].setString("Upgrading  " + to_string(turret.qDamage.front().getPrice()) + "$");
		text[3].setFillColor(bright);
	}
	else
	{
		text[3].setString("Upgrading  ---");
		text[3].setFillColor(dark);
	}
	if (turret.qRange.size() > 1)
	{
		text[4].setString("Upgrading  " + to_string(turret.qRange.front().getPrice()) + "$");
		text[4].setFillColor(bright);
	}
	else
	{
		text[4].setString("Upgrading  ---");
		text[4].setFillColor(dark);
	}
	if (turret.qRate.size() > 1)
	{
		text[5].setString("Upgrading  " + to_string(turret.qRate.front().getPrice()) + "$");
		text[5].setFillColor(bright);
	}
	else
	{
		text[5].setString("Upgrading  ---");
		text[5].setFillColor(dark);
	}
}

void Texts::updateInfo()
{
	text[0].setString("Damage");
	text[1].setString("Range");
	text[2].setString("Rate");
	text[0].setFillColor(dark);
	text[1].setFillColor(dark);
	text[2].setFillColor(dark);
	text[3].setString("Upgrading");
	text[4].setString("Upgrading");
	text[5].setString("Upgrading");
	text[3].setFillColor(dark);
	text[4].setFillColor(dark);
	text[5].setFillColor(dark);
}

void Texts::updateStats(int & cash, int & kills, int & level)
{
	text[9].setString("Cash  " + to_string(cash) + "$");
	text[10].setString("Kills  " + to_string(kills));
	text[11].setString("Wave  " + to_string(level));
}

sf::Text & Texts::getText(int & i)
{
	return text[i];
}

bool Texts::upgradingTextClicked(RenderWindow & window, const int & i)
{
	return text[i].getGlobalBounds().contains((Vector2f)Mouse::getPosition(window));
}
