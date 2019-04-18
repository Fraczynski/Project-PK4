#include "Rest.h"

using namespace std;

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
