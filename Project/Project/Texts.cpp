#include "Texts.h"

using namespace std;
using namespace sf;

Texts::Texts(const Font & font, Vector2f vectorTurret1, Vector2f vectorTurret2, Vector2f vectorTurret3, Turret *turret1, Turret *turret2, Turret *turret3)	//konstruktor tworzacy teksty
{
	for (int i = 0; i < 21; i++)			//ustawienia graficzne wszystkich tekstow
	{
		text[i].setFont(font);
		text[i].setCharacterSize(18);
		text[i].setOrigin(0, text[i].getGlobalBounds().height / 2);
	}
	text[0].setPosition(487, 627);		//ustawianie pozycji i zawartosci tekstow
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
	text[12].setPosition(55, 627);
	text[12].setString("Damage  " + to_string(turret1->damage));
	text[13].setPosition(70, 649);
	text[13].setString("Range  " + to_string(turret1->range));
	text[14].setPosition(83, 671);
	text[14].setString("Rate  " + to_string(turret1->rate));
	text[15].setPosition(216, 627);
	text[15].setString("Damage  " + to_string(turret2->damage));
	text[16].setPosition(231, 649);
	text[16].setString("Range  " + to_string(turret2->range));
	text[17].setPosition(244, 671);
	text[17].setString("Rate  " + to_string(turret2->rate));
	text[18].setPosition(376, 627);
	text[18].setString("Damage  " + to_string(turret3->damage));
	text[19].setPosition(391, 649);
	text[19].setString("Range  " + to_string(turret3->range));
	text[20].setPosition(404, 671);
	text[20].setString("Rate  " + to_string(turret3->rate));
}

void Texts::updateInfo(Turret & turret)					//wyswietlanie informacji o wiezyczce (przenoszonej lub klikniêtej)
{
	text[0].setString("Damage  " + to_string(turret.damage));			//informacje o danej wiezyczce
	text[1].setString("Range  " + to_string(turret.range));
	text[2].setString("Rate  " + to_string(turret.rate));
	text[0].setFillColor(bright);			//podswietlenie informacji
	text[1].setFillColor(bright);
	text[2].setFillColor(bright);
	if (turret.qDamage.size() > 1)			//koszt ulepszenia zadawanych obrazen
	{
		text[3].setString("Upgrading  " + to_string(turret.qDamage.front().getPrice()) + "$");
		text[3].setFillColor(bright);
	}
	else				//brak mozliwosci dalszego ulepszania zadawanych obrazen
	{
		text[3].setString("Upgrading  ---");
		text[3].setFillColor(dark);
	}
	if (turret.qRange.size() > 1)			//koszt ulepszenia zasiegu
	{
		text[4].setString("Upgrading  " + to_string(turret.qRange.front().getPrice()) + "$");
		text[4].setFillColor(bright);
	}
	else				//brak mozliwosci dalszego ulepszania zasiegu
	{
		text[4].setString("Upgrading  ---");
		text[4].setFillColor(dark);
	}
	if (turret.qRate.size() > 1)			//koszt ulepszenia czestotliwosci strzalow
	{
		text[5].setString("Upgrading  " + to_string(turret.qRate.front().getPrice()) + "$");
		text[5].setFillColor(bright);
	}
	else				//brak mozliwosci dalszego ulepszania czestotliwosci strzalow
	{
		text[5].setString("Upgrading  ---");
		text[5].setFillColor(dark);
	}
}

void Texts::updateInfo()			//przyciemnianie informacji o wiezyczce (zadna nie jest klikniêta)
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

void Texts::updateStats(int & cash, int & kills, int & level)			//aktualizowanie tekstu zawierajacego statystyki gry
{
	text[9].setString("Cash  " + to_string(cash) + "$");
	text[10].setString("Kills  " + to_string(kills));
	text[11].setString("Wave  " + to_string(level));
}

void Texts::display(int & cash, int & kills, int & level, RenderWindow & window)			//wyswietlanie tekstów
{
	updateStats(cash, kills, level);			//aktualizacja statystyk
	for (int i = 0; i < 21; i++)		//rysowanie wszystkich tekstow
	{
		window.draw(text[i]);
	}
}

int Texts::upgradingTextClicked(RenderWindow & window)			//sprawdzanie, czy kliknieto przycisk ulepszania
{
	if (text[3].getGlobalBounds().contains((Vector2f)Mouse::getPosition(window)))			//zwracanie numeru kliknietego przycisku
		return 1;
	if (text[4].getGlobalBounds().contains((Vector2f)Mouse::getPosition(window)))
		return 2;
	if (text[5].getGlobalBounds().contains((Vector2f)Mouse::getPosition(window)))
		return 3;
}
