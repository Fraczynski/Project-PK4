#include "Upgrading.h"

Upgrading::Upgrading(const int _price, const int _value) : price(_price), value(_value)				//konstruktor przypisujacy wartosci zmiennym
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
