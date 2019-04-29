#pragma once

class Upgrading			//klasa przechowujaca pare liczb - cene i wartosc ulepszenia
{
	int price;			//cena ulepszenia
	int value;			//wartosc ulepszenia

public:
	Upgrading(const int _price, const int _value);		//konstruktor przypisujacy wartosci zmiennym
	int getPrice();			//pobieranie ceny ulepszenia
	int getValue();			//pobieranie wartosci ulepszenia
};