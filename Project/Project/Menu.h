#pragma once
#include "GUI.h"

class Menu
{
public:
	Menu();
	~Menu();
	void menu(GUI & gui, vector<Map> & mapCorners);
	bool menuEvents(GUI & gui);
};

