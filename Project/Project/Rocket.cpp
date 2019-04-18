#include "Rocket.h"

using namespace std;
using namespace sf;

Rocket::Rocket(int _speed, int _damage, int _rotation, int _numberOfMonster, Texture & _picture, Vector2f _position) :
			   speed(_speed), damage(_damage), numberOfMonster(_numberOfMonster)					//konstruktor tworzacy pocisk
{
	picture.setTexture(_picture);
	picture.setOrigin(picture.getGlobalBounds().width / 2, picture.getGlobalBounds().height / 3);
	picture.setPosition(_position);
	picture.setRotation(_rotation);
}

bool Rocket::checkCollision(vector<Monster> & monsters, int & cash, int & kills)			//sprawdzanie wyst¹pienia kolizji z potworem
{
	for (unsigned j = 0; j < monsters.size(); j++)
	{
		if (picture.getGlobalBounds().contains(monsters[j].picture.getPosition()))				//sprawdzanie, czy obrazek zawiera punkt bedacy srodkiem obrazka potwora
			//monsters[j].picture.getGlobalBounds().contains(picture.getPosition()))
		{
			if (monsters[j].hurt(getDamage()))			//zadawanie obrazen potworowi
			{
				kills++;						//zabijanie potwora
				cash += monsters[j].getLevel();
				monsters.erase(monsters.begin() + j);
				j--;
				numberOfMonster = -1;
			}
			return true;		//wystapienie kolizji
		}
	}
	return false;			//brak kolizji
}

int Rocket::getDamage()			//pobieranie ilosci zadawanych obrazen
{
	return damage;
}

void Rocket::display(RenderWindow & window)			//wyswietlanie pocisku
{
	window.draw(picture);
}
