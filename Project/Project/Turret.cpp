#include "Turret.h"

using namespace std;
using namespace sf;

Turret::Turret(const int _id,  const Texture & _picture, const Vector2f _position) : id(_id)				//konstruktor tworzacy wiezyczke (uzywany dla wiezyczek w menu)
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

void Turret::loadParameters(const float & positionX, const float & positionY, const int & _timeToShoot, const int & _damage, const int & _range, const int & _rate,
	const int & _aimAtMonster, const float & rotation)
{
	picture.setPosition(Vector2f(positionX, positionY));
	picture.setRotation(rotation);
	timeToShoot = _timeToShoot;
	damage = _damage;
	range = _range;
	rate = _rate;
	aimAtMonster = _aimAtMonster;
	while (qDamage.size() > 1 && qDamage.front().getValue() <= damage)
	{
		qDamage.pop();
	}
	while (qRange.size() > 1 && qRange.front().getValue() <= range)
	{
		qRange.pop();
	}
	while (qRate.size() > 1 && qRate.front().getValue() >= rate)
	{
		qRate.pop();
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

int Turret::getID()
{
	return id;
}

int Turret::getDamage()
{
	return damage;
}

int Turret::getPrice()
{
	return price;
}

int Turret::getRange()
{
	return range;
}

int Turret::getRate()
{
	return rate;
}

int Turret::getSize(int queue)
{
	switch (queue)
	{
	case 0:
		return qDamage.size();
	case 1:
		return qRange.size();
	case 2:
		return qRate.size();
	}
}

int Turret::getFrontPrice(int queue)
{
	switch (queue)
	{
	case 0:
		return qDamage.front().getPrice();
	case 1:
		return qRange.front().getPrice();
	case 2:
		return qRate.front().getPrice();
	}
}

void Turret::setPosition(const Vector2f & vectorTurret)
{
	picture.setPosition(vectorTurret);
}

Vector2f Turret::getPosition()
{
	return picture.getPosition();
}

int Turret::getWidth()
{
	return picture.getGlobalBounds().width;
}

int Turret::getHeight()
{
	return picture.getGlobalBounds().height;
}

bool Turret::contains(const sf::Vector2f & point)
{
	return picture.getGlobalBounds().contains(point);
}

float Turret::getRotation()
{
	return picture.getRotation();
}

void Turret::rotate(vector<Monster> & monsters)			//obracanie wiezyczki w strone odpowiedniego potwora
{
	for (unsigned i = 0; i < monsters.size(); i++)				//szukanie potwora znajdujacego sie w zasiegu wiezyczki
	{
		if (isInRange(monsters[i]))					//sprawdzanie, czy potwor znajduje sie w zasiegu wiezyczki
		{
			double angle = (atan2(monsters[i].getPosition().y - picture.getPosition().y,
				monsters[i].getPosition().x - picture.getPosition().x) * (180 / (atan(1) * 4)) + 90);		//kat miedzy wiezyczka a potworem
			double rotation = picture.getRotation();				//aktualny kat obrocenia wiezyczki

			if (angle < 0)
				angle += 360;		//zakres kata miedzy wiezyczka o potworem: 0 : 360
			rotation -= angle;		//kat o jaki nalezy obrocic wiezyczke w strone potwora

			//operacje na kacie by zakres wynosil miedzy -180 a +180
			if (rotation < 0)
				rotation += 360;
			if (rotation > 180)
				rotation -= 360;

			if (rotation >= 0)
				picture.rotate(-sqrt(rotation) / 2);		//obracanie w lewo
			else
				picture.rotate(sqrt(-rotation) / 2);		//obracanie w prawo
			
			aimAtMonster = i;			//zapisanie numeru potwora, w ktory wycelowala wiezyczka
			return;
		}
	}
	aimAtMonster = -1;			//brak potwora w zasiegu wiezyczki
}

int Turret::shoot(const vector<Monster> & monsters)				//strzelanie do odpowiedniego potwora
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

bool Turret::isInRange(Monster & m)			//sprawdzanie czy dany potwor jest w zasiegu wiezyczki
{
	if (sqrt(pow(m.getPosition().x - picture.getPosition().x, 2) + pow(m.getPosition().y - picture.getPosition().y, 2)) < range)	
																							//sprawdanie, czy odleglosc miedzy wiezyczka a potworem jest mniejsza od zasiegu wiezyczki
	{
		return true;
	}
	return false;
}

void Turret::upgrade(const int upgrading, int & cash)			//ulepszanie danej cechy wiezyczki
{
	switch (upgrading)			//sprawdzanie, ktora cecha jest ulepszana
	{
	case 1:
		if (qDamage.size() > 1 && cash - qDamage.front().getPrice() >= 0)	//sprawdzanie czy gracz ma wystarczajaca ilosc pieniedzy i czy jest mozliwosc dalszego ulepszania zadawanych obrazen
		{
			cash -= qDamage.front().getPrice();			//zmniejszanie ilosci pieniedzy
			damage = qDamage.front().getValue();		//aktualizacja wartosci zadawanych obrazen
			qDamage.pop();				//usuwanie wartosci ulepszenia z kolejki
		}
		break;
	case 2:
		if (qRange.size() > 1 && cash - qRange.front().getPrice() >= 0)		//sprawdzanie czy gracz ma wystarczajaca ilosc pieniedzy i czy jest mozliwosc dalszego ulepszania zasiegu
		{
			cash -= qRange.front().getPrice();			//zmniejszanie ilosci pieniedzy
			range = qRange.front().getValue();		//aktualizacja wartosci zasiegu
			qRange.pop();				//usuwanie wartosci ulepszenia z kolejki
		}
		break;
	case 3:
		if (qRate.size() > 1 && cash - qRate.front().getPrice() >= 0)		//sprawdzanie czy gracz ma wystarczajaca ilosc pieniedzy i czy jest mozliwosc dalszego ulepszania czestotliwosci ulepszania
		{
			cash -= qRate.front().getPrice();			//zmniejszanie ilosci pieniedzy
			rate = qRate.front().getValue();		//aktualizacja wartosci czestotliwosci strzelania
			qRate.pop();				//usuwanie wartosci ulepszenia z kolejki
		}
		break;
	}
}

void Turret::display(sf::RenderWindow & window)
{
	window.draw(picture);
}

void Turret::save(fstream & file)
{
	file << id << " " << (int)picture.getPosition().x << " " << (int)picture.getPosition().y << " " << timeToShoot << " " << damage << " " << range << " " << rate << " ";
	file << aimAtMonster << " " << (int)picture.getRotation() << endl;
}