#include "Rocket1.h"

using namespace std;
using namespace sf;

Rocket1::Rocket1(const int & _id, const int & _speed, const int & _damage, const int & _rotation, const int & _numberOfMonster, sf::Texture & _picture, sf::Vector2f _position) :
				Rocket(_id, _speed, _damage, _rotation, _numberOfMonster, _picture, _position)						//konstruktor tworzacy pocisk
{

}

bool Rocket1::specialAbilities(vector<Monster> & monsters, int & cash, int & kills)			//specjalne zdolnosci tego typu pocisku (rakieta)
{
	if (monsters.empty() || monsters.begin()->getPosition().y < 0)		//sprawdzanie, czy sa potwory na mapie
	{
		picture.rotate(3);					//jesli nie to poruszanie sie po okregu pocisku
		picture.move(sin((picture.getRotation()) * ((atan(1) * 4) / 180)) * speed, -cos((picture.getRotation()) * ((atan(1) * 4) / 180)) * speed);
	}
	else if(numberOfMonster < monsters.size() && numberOfMonster >= 0)			//sprawdzanie, czy pocisk wycelowany jest w istniejacego potwora
	{
		picture.setRotation(atan2(monsters[numberOfMonster].getPosition().y - picture.getPosition().y,
			monsters[numberOfMonster].getPosition().x - picture.getPosition().x) * (180 / (atan(1) * 4)) + 90);		//obracanie pocisku w kierunku potwora
		picture.move(sin((picture.getRotation()) * ((atan(1) * 4) / 180)) * speed, -cos((picture.getRotation()) * ((atan(1) * 4) / 180)) * speed);		//przesuwanie pocisku

		return checkCollision(monsters, cash, kills);		//zwracanie informacji, czy wystapila kolizja
	}
	else				//potwor, na ktory zostal wycelowany pocisk, zostal zabity
	{
		numberOfMonster = -1;		//celowanie w potwora, ktory jest najblizej bazy
		picture.setRotation(atan2(monsters.begin()->getPosition().y - picture.getPosition().y,
			monsters.begin()->getPosition().x - picture.getPosition().x) * (180 / (atan(1) * 4)) + 90);			//obracanie w kierunku potwora znajdujacego sie najblizej mapy
		picture.move(sin((picture.getRotation()) * ((atan(1) * 4) / 180)) * speed, -cos((picture.getRotation()) * ((atan(1) * 4) / 180)) * speed);		//przesuwanie w jego kierunku

		return checkCollision(monsters, cash, kills);		//zwracanie informacji czy wystapila kolizja
	}
	return false;
}