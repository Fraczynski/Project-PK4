#include "Rest.h"
#include <string.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>

using namespace std;
using namespace sf;

void upgradingTurret(const int & id, queue<Upgrading> & qDamage, queue<Upgrading> & qRange, queue<Upgrading> & qRate)
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
		qRange.push(Upgrading(35, 250));
		qRange.push(Upgrading(100, 280));
		qRange.push(Upgrading(300, 300));
		qRange.push(Upgrading(900, 320));
		qRange.push(Upgrading(1200, 340));
		qRange.push(Upgrading(1500, 350));
		qRange.push(Upgrading(0, 0));
		qRate.push(Upgrading(30, 100));
		qRate.push(Upgrading(60, 90));
		qRate.push(Upgrading(150, 70));
		qRate.push(Upgrading(340, 50));
		qRate.push(Upgrading(600, 40));
		qRate.push(Upgrading(1100, 30));
		qRate.push(Upgrading(1500, 20));
		qRate.push(Upgrading(0, 0));
		break;
	case 2:
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
		qRange.push(Upgrading(35, 250));
		qRange.push(Upgrading(100, 280));
		qRange.push(Upgrading(300, 300));
		qRange.push(Upgrading(900, 320));
		qRange.push(Upgrading(1200, 340));
		qRange.push(Upgrading(1500, 350));
		qRange.push(Upgrading(0, 0));
		qRate.push(Upgrading(30, 100));
		qRate.push(Upgrading(60, 90));
		qRate.push(Upgrading(150, 70));
		qRate.push(Upgrading(340, 50));
		qRate.push(Upgrading(600, 40));
		qRate.push(Upgrading(1100, 30));
		qRate.push(Upgrading(1500, 20));
		qRate.push(Upgrading(0, 0));
		break;
	case 3:

		break;
	}
}

Upgrading::Upgrading(int _price, int _value) : price(_price), value(_value)
{

}

int Upgrading::getPrice()
{
	return price;
}

int Upgrading::getValue()
{
	return value;
}
