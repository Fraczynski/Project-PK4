#include "Turret.h"

using namespace std;
using namespace sf;


Turret::Turret(int _id,  Texture & _picture, Vector2f _position) : id(_id)				//konstruktor tworzacy wiezyczke (uzywany dla wiezyczek w menu)
{
	picture.setTexture(_picture);
	picture.setPosition(_position);
	if (id == 2)
		picture.setOrigin(picture.getGlobalBounds().width / 2, picture.getGlobalBounds().height / 1.8);
	else
		picture.setOrigin(picture.getGlobalBounds().width / 2, picture.getGlobalBounds().height / 2);
	switch (_id)			//ustawianie poczatkowych wartosci danej wiezyczki
	{
	case 1:
		price = 20;
		damage = 3;
		range = 200;
		rate = 140;
		upgradingTurret();
		break;
	case 2:
		price = 10;
		damage = 1;
		range = 150;
		rate = 100;
		upgradingTurret();
		break;
	case 3:
		price = 50;
		damage = 1;
		range = 100;
		rate = 100;
		upgradingTurret();
		break;
	}
}

Turret::Turret(const Turret & _turret) : id(_turret.id),  damage(_turret.damage), rate(_turret.rate), range(_turret.range)
{																//konstruktor tworzacy kopie wiezyczki (uzywany przy budowaniu wiezyczki na mapie - kopia danej wiezyczki z menu)
	picture.setTexture(*(_turret.picture.getTexture()));
	picture.setPosition(_turret.picture.getPosition());
	picture.setOrigin(_turret.picture.getOrigin());
	switch (id)		//ustawianie kolejek z wartosciami kolejnych ulepszen
	{
	case 1:
		upgradingTurret();
		break;
	case 2:
		upgradingTurret();
		break;
	case 3:
		upgradingTurret();
		break;
	}
}

void Turret::upgradingTurret()				//wypelnianie kolejek wartosciami kolejnych ulepszen wraz z ich cenami
{
	switch (id)
	{
	case 1:
		qDamage.push(Upgrading(50, 8));
		qDamage.push(Upgrading(100, 13));
		qDamage.push(Upgrading(200, 18));
		qDamage.push(Upgrading(350, 23));
		qDamage.push(Upgrading(650, 28));
		qDamage.push(Upgrading(1000, 33));
		qDamage.push(Upgrading(1200, 38));
		qDamage.push(Upgrading(1300, 43));
		qDamage.push(Upgrading(1500, 48));
		qDamage.push(Upgrading(0, 0));
		qRange.push(Upgrading(35, 220));
		qRange.push(Upgrading(100, 240));
		qRange.push(Upgrading(300, 260));
		qRange.push(Upgrading(900, 280));
		qRange.push(Upgrading(1200, 315));
		qRange.push(Upgrading(1500, 350));
		qRange.push(Upgrading(0, 0));
		qRate.push(Upgrading(30, 120));
		qRate.push(Upgrading(60, 100));
		qRate.push(Upgrading(150, 80));
		qRate.push(Upgrading(340, 60));
		qRate.push(Upgrading(600, 40));
		qRate.push(Upgrading(1100, 30));
		qRate.push(Upgrading(1500, 20));
		qRate.push(Upgrading(0, 0));
		break;
	case 2:
		qDamage.push(Upgrading(50, 2));
		qDamage.push(Upgrading(100, 3));
		qDamage.push(Upgrading(200, 4));
		qDamage.push(Upgrading(350, 5));
		qDamage.push(Upgrading(650, 6));
		qDamage.push(Upgrading(1000, 7));
		qDamage.push(Upgrading(1200, 8));
		qDamage.push(Upgrading(1300, 9));
		qDamage.push(Upgrading(1500, 10));
		qDamage.push(Upgrading(0, 0));
		qRange.push(Upgrading(35, 170));
		qRange.push(Upgrading(100, 180));
		qRange.push(Upgrading(300, 200));
		qRange.push(Upgrading(900, 220));
		qRange.push(Upgrading(1200, 240));
		qRange.push(Upgrading(1500, 260));
		qRange.push(Upgrading(0, 0));
		qRate.push(Upgrading(30, 90));
		qRate.push(Upgrading(60, 80));
		qRate.push(Upgrading(150, 70));
		qRate.push(Upgrading(340, 55));
		qRate.push(Upgrading(600, 40));
		qRate.push(Upgrading(1100, 30));
		qRate.push(Upgrading(1500, 20));
		qRate.push(Upgrading(0, 0));
		break;
	case 3:
		qDamage.push(Upgrading(50, 2));
		qDamage.push(Upgrading(100, 3));
		qDamage.push(Upgrading(200, 4));
		qDamage.push(Upgrading(350, 5));
		qDamage.push(Upgrading(650, 6));
		qDamage.push(Upgrading(1000, 7));
		qDamage.push(Upgrading(1200, 8));
		qDamage.push(Upgrading(1300, 9));
		qDamage.push(Upgrading(1500, 10));
		qDamage.push(Upgrading(0, 0));
		qRange.push(Upgrading(35, 120));
		qRange.push(Upgrading(100, 140));
		qRange.push(Upgrading(300, 160));
		qRange.push(Upgrading(900, 180));
		qRange.push(Upgrading(1200, 200));
		qRange.push(Upgrading(1500, 220));
		qRange.push(Upgrading(0, 0));
		qRate.push(Upgrading(30, 90));
		qRate.push(Upgrading(60, 80));
		qRate.push(Upgrading(150, 70));
		qRate.push(Upgrading(340, 55));
		qRate.push(Upgrading(600, 40));
		qRate.push(Upgrading(1100, 30));
		qRate.push(Upgrading(1500, 20));
		qRate.push(Upgrading(0, 0));
		break;
	}
}

int Turret::getPrice()				//pobieranie ceny wiezyczki
{
	return price;
}

void Turret::rotate(const vector<Monster> & monsters)			//obracanie wiezyczki w strone odpowiedniego potwora
{
	for (unsigned i = 0; i < monsters.size(); i++)				//szukanie potwora znajdujacego sie w zasiegu wiezyczki
	{
		if (isInRange(monsters[i]))					//sprawdzanie, czy potwor znajduje sie w zasiegu wiezyczki
		{
			picture.setRotation(atan2(monsters[i].picture.getPosition().y - picture.getPosition().y,
				monsters[i].picture.getPosition().x - picture.getPosition().x) * (180 / (atan(1) * 4)) + 90);			//obracanie wiezyczki w kierunku potwora
			aimAtMonster = i;			//zapisanie numeru potwora, w ktory wycelowala wiezyczka
			return;
		}
	}
	aimAtMonster = -1;			//brak potwora w zasiegu wiezyczki
	/*
	//double angle = (360 - (double)((int)(270 - ((atan2(monsters.begin()->picture.getPosition().y - i->picture.getPosition().y, 
						monsters.begin()->picture.getPosition().x - i->picture.getPosition().x)) * (180 / (atan(1) * 4)))) % 360) - i->picture.getRotation());
	//i->picture.rotate(360 - (270 - (atan2(monsters.begin()->picture.getPosition().y - i->picture.getPosition().y, 
						monsters.begin()->picture.getPosition().x - i->picture.getPosition().x)) * (180 / (atan(1) * 4))) - i->picture.getRotation());

	if (angle > 1 && angle <= 180)
	{
		i->picture.rotate(angle / 20);
	}
	else if (angle > 180 || angle < -1)
	{
		i->picture.rotate(-(360 - angle) % 180 / 20);
	}
	else
	{
		i->picture.rotate(angle);
	}*/
}

int Turret::shoot(vector<Monster> & monsters)				//strzelanie do odpowiedniego potwora
{
	if (timeToShoot > 0)		//czekanie na mozliwosc wystrzalu
	{
		timeToShoot--;			//zmniejszanie pozostalego czasu do wystrzalu
		return -1;
	}
	else
	{
		if (aimAtMonster >= 0 && aimAtMonster < monsters.size())		//sprawdzanie, czy wiezyczka wycelowala na potwora
		{
			timeToShoot = rate;			//odnowienie czasu oczekiwania na mozliwosc wystrzalu
			return aimAtMonster;		//zwracanie numeru potwora, na ktory wycelowana jest wiezyczka
		}
	}
}

bool Turret::isInRange(const Monster & m)			//sprawdzanie czy dany potwor jest w zasiegu wiezyczki
{
	if (sqrt(pow(m.picture.getPosition().x - picture.getPosition().x, 2) + pow(m.picture.getPosition().y - picture.getPosition().y, 2)) < range)	
																							//sprawdanie, czy odleglosc miedzy wiezyczka a potworem jest mniejsza od zasiegu wiezyczki
	{
		return true;
	}
	return false;
}

void Turret::upgrade(int upgrading, int & cash)			//ulepszanie danej cechy wiezyczki
{
	switch (upgrading)			//sprawdzanie, ktora cecha jest ulepszana
	{
	case 1:
		if (cash - qDamage.front().getPrice() >= 0 && qDamage.size() > 1)	//sprawdzanie czy gracz ma wystarczajaca ilosc pieniedzy i czy jest mozliwosc dalszego ulepszania zadawanych obrazen
		{
			cash -= qDamage.front().getPrice();			//zmniejszanie ilosci pieniedzy
			damage = qDamage.front().getValue();		//aktualizacja wartosci zadawanych obrazen
			qDamage.pop();				//usuwanie wartosci ulepszenia z kolejki
		}
		break;
	case 2:
		if (cash - qRange.front().getPrice() >= 0 && qRange.size() > 1)		//sprawdzanie czy gracz ma wystarczajaca ilosc pieniedzy i czy jest mozliwosc dalszego ulepszania zasiegu
		{
			cash -= qRange.front().getPrice();			//zmniejszanie ilosci pieniedzy
			range = qRange.front().getValue();		//aktualizacja wartosci zasiegu
			qRange.pop();				//usuwanie wartosci ulepszenia z kolejki
		}
		break;
	case 3:
		if (cash - qRate.front().getPrice() >= 0 && qRate.size() > 1)		//sprawdzanie czy gracz ma wystarczajaca ilosc pieniedzy i czy jest mozliwosc dalszego ulepszania czestotliwosci ulepszania
		{
			cash -= qRate.front().getPrice();			//zmniejszanie ilosci pieniedzy
			rate = qRate.front().getValue();		//aktualizacja wartosci czestotliwosci strzelania
			qRate.pop();				//usuwanie wartosci ulepszenia z kolejki
		}
		break;
	}
}

Upgrading::Upgrading(int _price, int _value) : price(_price), value(_value)				//konstruktor przypisujacy wartosci zmiennym
{

}

int Upgrading::getPrice()			//pobieranie ceny ulepszenia
{
	return price;
}

int Upgrading::getValue()			//pobieranie wartosci ulepszenia
{
	return value;
}
