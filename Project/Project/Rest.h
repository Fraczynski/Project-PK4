#pragma once
#include <queue>

class Upgrading
{
	int price;
	int value;

public:
	Upgrading(int _price, int _value);
	int getPrice();
	int getValue();
};