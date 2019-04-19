#include "Rocket3.h"

using namespace std;
using namespace sf;

Rocket3::Rocket3(const int & _id, const int & _speed, const int & _damage, const int & _rotation, const int & _numberOfMonster, sf::Texture & _picture, sf::Vector2f _position) :
				Rocket(_id, _speed, _damage, _rotation, _numberOfMonster, _picture, _position)				//konstruktor tworzacy pocisk (laser)
{
	picture.setOrigin(_picture.getSize().x / 2 , _picture.getSize().y);				//os obrotu lasera na srodku krotszego boku
}

bool Rocket3::specialAbilities(vector<Monster> & monsters, int & cash, int & kills)				//specjalne zdolnosci tego typu pocisku (laser)
{
	if (--timeOfLife <= 0)				//koniec czasu zycia lasera
	{
		return true;
	}
	else if (numberOfMonster < monsters.size() && numberOfMonster >= 0)		//sprawdzanie, czy laser wycelowany jest w istniejacego potwora
	{
		if (checkCollision(monsters, cash, kills))		//sprawdzanie, czy wystapila kolizja z potworem
			damage = 0;			//usuwanie mozliwosci zadawania obrazen danego lasera, by zniknal dopiero jak skonczy sie jego czas zycia
	}
	return false;
}
