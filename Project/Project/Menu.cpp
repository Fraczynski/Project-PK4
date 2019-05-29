#include "Menu.h"

using namespace std;
using namespace sf;

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::menu(GUI & gui, list<Map> & mapCorners)
{
	//ustawianie tel i map do menu
	gui.setMenuGraphics();

	//wyswietlanie calego menu
	while (!menuEvents(gui))
	{
		gui.displayMenu();
	}

	//resetowanie ustawien grafik map i tel
	if (gui.isOpen())
	{
		gui.checkCorners(mapCorners);
		gui.resetMenuGraphics();
	}
}

bool Menu::menuEvents(GUI & gui)
{
	Event e;
	while (gui.pollEvent(e))
	{
		if (e.type == Event::Closed)
		{
			gui.close();
			return true;
		}
		if (e.type == Event::MouseButtonReleased && e.mouseButton.button == Mouse::Left)
		{
			if (gui.isButtonMapClicked())
				return true;
		}
	}
	return false;
}
