#include "Rocket1.h"

using namespace std;
using namespace sf;

Rocket1::Rocket1(int _speed, int _damage, int _rotation, int _rotationSpeed, int _numberOfMonster, Texture & _picture, Vector2f _position) : 
				Rocket(_speed, _damage, _rotation, _numberOfMonster, _picture, _position), rotationSpeed(_rotationSpeed)			//konstruktor tworzacy pocisk
{

}

bool Rocket1::specialAbilities(vector<Monster> & monsters, int & cash, int & kills)			//specjalne zdolnosci tego typu pocisku (rakieta)
{
	if (monsters.empty() || monsters.begin()->picture.getPosition().y < 0)		//sprawdzanie, czy sa potwory na mapie
	{
		picture.rotate(3);					//jesli nie to poruszanie sie po okregu pocisku
		picture.move(sin((picture.getRotation()) * ((atan(1) * 4) / 180)) * speed, -cos((picture.getRotation()) * ((atan(1) * 4) / 180)) * speed);
	}
	else if(numberOfMonster < monsters.size() && numberOfMonster >= 0)			//sprawdzanie, czy pocisk wycelowany jest w istniejacego potwora
	{
		picture.setRotation(atan2(monsters[numberOfMonster].picture.getPosition().y - picture.getPosition().y,
			monsters[numberOfMonster].picture.getPosition().x - picture.getPosition().x) * (180 / (atan(1) * 4)) + 90);		//obracanie pocisku w kierunku potwora
		picture.move(sin((picture.getRotation()) * ((atan(1) * 4) / 180)) * speed, -cos((picture.getRotation()) * ((atan(1) * 4) / 180)) * speed);		//przesuwanie pocisku

		return checkCollision(monsters, cash, kills);		//zwracanie informacji, czy wystapila kolizja
	}
	else				//potwor, na ktory zostal wycelowany pocisk, zostal zabity
	{
		numberOfMonster = -1;		//celowanie w potwora, ktory jest najblizej bazy
		picture.setRotation(atan2(monsters.begin()->picture.getPosition().y - picture.getPosition().y,
			monsters.begin()->picture.getPosition().x - picture.getPosition().x) * (180 / (atan(1) * 4)) + 90);			//obracanie w kierunku potwora znajdujacego sie najblizej mapy
		picture.move(sin((picture.getRotation()) * ((atan(1) * 4) / 180)) * speed, -cos((picture.getRotation()) * ((atan(1) * 4) / 180)) * speed);		//przesuwanie w jego kierunku

		return checkCollision(monsters, cash, kills);		//zwracanie informacji czy wystapila kolizja
	}
	return false;
}