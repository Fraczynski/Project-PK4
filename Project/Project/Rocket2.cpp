#include "Rocket2.h"

using namespace std;
using namespace sf;

Rocket2::Rocket2(const int & _id, const int & _speed, const int & _damage, const int & _rotation, const int & _numberOfMonster, sf::Texture & _picture, sf::Vector2f _position) :
				Rocket(_id, _speed, _damage, _rotation, _numberOfMonster, _picture, _position)			//konstruktor tworzacy pocisk
{
	
}

bool Rocket2::specialAbilities(vector<Monster> & monsters, int & cash, int & kills)				//specjalne zdolnosci tego typu pocisku (kulka)
{
	picture.move(sin((picture.getRotation()) * ((atan(1) * 4) / 180)) * speed, -cos((picture.getRotation()) * ((atan(1) * 4) / 180)) * speed);		//przesuwanie pocisku
	if (monsters.empty() || monsters.begin()->getPosition().y < 0)		//potwory poza mapa
	{
		return false;			//brak kolizji
	}
	else if(numberOfMonster < monsters.size() && numberOfMonster >= 0)		//sprawdzenie, czy znajduje sie potwor na mapie
	{
		return checkCollision(monsters, cash, kills);		//zwracanie informacji, czy wystapila kolizja
	}
	return false;		//brak kolizji
}