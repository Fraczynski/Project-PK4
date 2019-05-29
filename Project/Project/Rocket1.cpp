#include "Rocket1.h"

using namespace std;
using namespace sf;

Rocket1::Rocket1(const int & _id, const int & _speed, const int & _damage, const int & _rotation, const int & _numberOfMonster, sf::Texture & _picture, sf::Vector2f _position) :
				Rocket(_id, _speed, _damage, _rotation, _numberOfMonster, _picture, _position)						//konstruktor tworzacy pocisk
{

}

bool Rocket1::specialAbilities(vector<Monster> & monsters, int & cash, int & kills)			//specjalne zdolnosci tego typu pocisku (rakieta)
{
	if(numberOfMonster >= 0 && numberOfMonster < (int)monsters.size() && monsters[numberOfMonster].getPosition().y > 0)			//sprawdzanie, czy pocisk wycelowany jest w istniejacego potwora
	{
		double angle = (atan2(monsters[numberOfMonster].getPosition().y - picture.getPosition().y, 
						monsters[numberOfMonster].getPosition().x - picture.getPosition().x) * (180 / (atan(1) * 4)) + 90);		//kat miedzy rakieta a potworem
		double rotation = picture.getRotation();				//aktualny kat obrocenia rakiety

		if (angle < 0)
			angle += 360;		//zakres kata miedzy rakieta o potworem: 0 : 360
		rotation -= angle;		//kat o jaki nalezy obrocic rakiete w strone potwora

		//operacje na kacie by zakres wynosil miedzy -180 a +180
		if (rotation < 0)
			rotation += 360;
		if (rotation > 180)
			rotation -= 360;

		if (rotation >= 0)
			picture.rotate(-(float)sqrt(rotation) / 2);		//obracanie w lewo
		else
			picture.rotate((float)sqrt(-rotation) / 2);		//obracanie w prawo
		
		picture.move((float)sin((picture.getRotation()) * ((atan(1) * 4) / 180)) * speed, -(float)cos((picture.getRotation()) * ((atan(1) * 4) / 180)) * speed);		//przesuwanie pocisku
				
		return checkCollision(monsters, cash, kills);		//zwracanie informacji, czy wystapila kolizja
	}
	else if((numberOfMonster >= (int)monsters.size() && numberOfMonster != 0) || numberOfMonster < 0)		//sprawdzanie, czy pocisk wycelowany jest w nieistniejacego
	{
		numberOfMonster = 0;
	}
	else					//jesli nie to poruszanie sie pocisku po okregu
	{
		picture.rotate(3);
		picture.move((float)sin((picture.getRotation()) * ((atan(1) * 4) / 180)) * speed, -(float)cos((picture.getRotation()) * ((atan(1) * 4) / 180)) * speed);
	}
	return false;
}
