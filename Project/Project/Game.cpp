#include <vector>
#include <fstream>
#include "Game.h"

using namespace std;
using namespace sf;

Game::Game()
{
	gui.loadGraphics();
	//ustawienie wiezyczek w menu
	turret1.reset(new Turret(1, gui.T_turret1, Vector2f(vectorTurret1)));
	turret2.reset(new Turret(2, gui.T_turret2, Vector2f(vectorTurret2)));
	turret3.reset(new Turret(3, gui.T_turret3, Vector2f(vectorTurret3)));
	gui.setTexts(turret1.get(), turret2.get(), turret3.get());
	resetGame();
}

void Game::guiMethods()
{
	gui.display(turrets, monsters, rockets, clicked, cash, kills, level, timeToNextRound, turret1.get(), turret2.get(), turret3.get());
	gui.endAnimation();
}

void Game::events()
{
	Event e;
	while (gui.pollEvent(e))
	{
		if (e.type == Event::Closed)
		{
			gui.close();
			return;
		}
		else if (e.type == Event::KeyReleased && e.key.code == Keyboard::Escape)
		{
			pause();
			if (!gui.isOpen())
				return;
		}
		else if (e.type == Event::MouseButtonReleased && e.mouseButton.button == Mouse::Left)
		{
			leftButtonReleased();
		}
		else if (e.type == Event::MouseButtonReleased && e.mouseButton.button == Mouse::Right)
		{
			resetTurrets();
		}
	}
}

//logika gry
bool Game::isPlayed()
{
	return gui.isOpen();
}

void Game::resetGame()
{
	timeToNextRound = 30;		//pozostaly czas do kolejnej rundy
	ifMovingTurret = 0;			//czy przenoszona aktualnie jest wiezyczka: 0 - nie; 1 - tak
	clicked = -1;				//numer zaznaczonej wiezyczki: -1 - brak zaznaczonej
	level = 0;					//numer aktualnego poziomu
	cash = 2000000;				//poczatkowa ilosc pieniedzy
	kills = 0;					//licznik zabitych potworow
	monsterPictureX = 0;		//wspolrzedna x aktualnego sprite'a potwora
	monsterPictureY = 0;		//wspolrzedna y aktualnego sprite'a potwora
	gui.updateInfo();

	//czyszczenie wszystkich wektorow
	monsters.clear();
	turrets.clear();
	rockets.clear();
	gui.linesClear();
	mapCorners.clear();

	//resetowanie sklepu
	resetTurrets();

	//for (int i = 0; i < 10; i++) { monsters.push_back(Monster(level, fontCalibri, T_monster, Vector2f(709, 300 - i * 30), monsterPictureX, monsterPictureY, monsterSize)); monsters.push_back(Monster(level, fontCalibri, T_monster, Vector2f(132, 400 - i * 30), monsterPictureX, monsterPictureY, monsterSize));}
}

void Game::resetTurrets()
{
	turret1->setPosition(vectorTurret1);
	turret2->setPosition(vectorTurret2);
	turret3->setPosition(vectorTurret3);
	gui.resetTurrets();
	ifMovingTurret = 0;
}

void Game::leftButtonReleased()
{
	Vector2i position = gui.getMousePosition();
	if (position.y >= 625)
	{
		if (position.x >= 921)
		{
			timeToNextRound = 0;
			return;
		}
		else if (!ifMovingTurret && notMovingTurret())
		{
			return;
		}
		else if (clicked >= 0 && clicked < (int)turrets.size() && !ifMovingTurret)
		{
			upgradeTurrets();
		}
	}
	else if (position.y <= 624)
	{
		if (ifMovingTurret)
		{
			movingTurret();
			return;
		}
		turretClicked();
	}
	
}

void Game::movingTurret()
{
	bool tmp = 0;
	switch (ifMovingTurret)
	{
	case 1:
		if (cash >= turret1->getPrice() && checkPlace(turret1->getPosition(), turret1->getWidth(), turret1->getHeight()))
		{
			tmp = 1;
			cash -= turret1->getPrice();
			turrets.push_back(*turret1);
		}
		break;
	case 2:
		if (cash >= turret2->getPrice() && checkPlace(turret2->getPosition(), turret2->getWidth(), turret2->getHeight()))
		{
			tmp = 1;
			cash -= turret2->getPrice();
			turrets.push_back(*turret2);
		}
		break;
	case 3:
		if (cash >= turret3->getPrice() && checkPlace(turret3->getPosition(), turret3->getWidth(), turret3->getHeight()))
		{
			tmp = 1;
			cash -= turret3->getPrice();
			turrets.push_back(*turret3);
		}
		break;
	}
	if (!tmp)
	{
		return;
	}
	resetTurrets();
}

void Game::moveTurret()
{
	switch (ifMovingTurret)
	{
	case 1:
		turret1->setPosition(gui.getMousePosition());
		gui.updateCircle(gui.getMousePosition(), turret1->getRange());
		break;
	case 2:
		turret2->setPosition(gui.getMousePosition());
		gui.updateCircle(gui.getMousePosition(), turret2->getRange());
		break;
	case 3:
		turret3->setPosition(gui.getMousePosition());
		gui.updateCircle(gui.getMousePosition(), turret3->getRange());
		break;
	}
}

bool Game::notMovingTurret()
{
	if (turret1->contains(gui.getMousePosition()))
	{
		gui.changeCursor(2);
		ifMovingTurret = 1;
		gui.updateInfo(*turret1);
		return true;
	}
	else if (turret2->contains(gui.getMousePosition()))
	{
		gui.changeCursor(2);
		ifMovingTurret = 2;
		gui.updateInfo(*turret2);
		return true;
	}
	else if (turret3->contains(gui.getMousePosition()))
	{
		gui.changeCursor(2);
		ifMovingTurret = 3;
		gui.updateInfo(*turret3);
		return true;
	}
	return false;
}

bool Game::turretClicked()
{
	for (unsigned i = 0; i < turrets.size(); i++)
	{
		if (turrets[i].contains(gui.getMousePosition()))
		{
			clicked = i;
			gui.updateCircle(Vector2i((turrets.begin() + clicked)->getPosition()), (turrets.begin() + clicked)->getRange());
			gui.updateInfo(*(turrets.begin() + clicked));
			return true;
		}
	}
	clicked = -1;
	gui.updateCircle(Vector2i(0, 0), 0);
	gui.updateInfo();
	return false;
}

void Game::upgradeTurrets()
{
	switch (gui.upgradingTextClicked())
	{
	case 1:
		turrets[clicked].upgrade(1, cash);
		break;
	case 2:
		turrets[clicked].upgrade(2, cash);
		break;
	case 3:
		turrets[clicked].upgrade(3, cash);
		break;
	}
	gui.updateCircle(Vector2i((turrets.begin() + clicked)->getPosition()), (turrets.begin() + clicked)->getRange());
	gui.updateInfo(*(turrets.begin() + clicked));
}

void Game::move_monsters()
{
	for (unsigned i = 0; i < monsters.size(); i++)
	{
		if (monsters[i].move(mapCorners))
		{
			gui.addLines();
			monsters.erase(monsters.begin() + i);
			i--;
		}
	}
}

void Game::add_monsters()
{
	if (timeToNextRound < 0)
	{
		timeToNextRound = roundTime;
		level++;
		for (int i = 0; i < 10; i++)
		{
			monsters.push_back(Monster(level, gui.fontCalibri, gui.T_monster, Vector2f(920, -60 * (float)i), monsterPictureX, monsterPictureY, monsterSize));
		}
		monsterPictureX += monsterSize;
		if (monsterPictureX >= (int)gui.T_monster.getSize().x)
		{
			monsterPictureX = 0;
			monsterPictureY += monsterSize;
			if (monsterPictureY >= (int)gui.T_monster.getSize().y)
			{
				monsterPictureY = 0;
			}
		}
	}
}

void Game::rotate_turrets()
{
	if (monsters.empty() == 0)
	{
		for (auto & t : turrets)
		{
			t.rotate(monsters);
		}
	}
}

void Game::move_missiles()
{
	for (int i = 0; i < (int)rockets.size(); i++)
	{
		if (rockets[i]->specialAbilities(monsters, cash, kills))
		{
			rockets.erase(rockets.begin() + i);
			i--;
		}
	}
}

bool Game::checkPlace(const Vector2f & position, const int & w, const int & h)
{
	int i;
	if (position.y + w / 2 + 3 <= 624)
	{
		for (
			(position.y - w / 2 - 3 >= 0) ? (i = (int)position.y - w / 2 - 3) : i = 0; i < position.y + w / 2 + 3 && i < gui.getHeight(); i++)
		{
			if (!gui.checkPixel((int)position.x, i) || !gui.checkPixel((int)position.x + w / 2 - 1, i))
			{
				return false;
			}
		}
		for (((int)position.x - w / 2 - 3 >= 0) ? (i = (int)position.x - w / 2 - 3) : (i = 0); i < (int)position.x + w / 2 + 3 && i < gui.getWidth(); i++)
		{
			if (!gui.checkPixel(i, (int)position.y) || !gui.checkPixel(i, (int)position.y + w / 2 - 1))
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}

	for (auto t : turrets)
	{
		if (sqrt(pow(t.getPosition().x - position.x, 2) + pow(t.getPosition().y - position.y, 2)) <= 53)
		{
			return false;
		}
	}
	return true;
}

void Game::shoot()
{
	int numberOfMonster;
	for (auto & t : turrets)
	{
		numberOfMonster = t.shoot(monsters);
		if (numberOfMonster >= 0 && numberOfMonster < (int)monsters.size())
		{
			switch (t.getID())
			{
			case 1:
				rockets.emplace_back(new Rocket1(1, 2, t.getDamage(), (int)t.getRotation(), numberOfMonster, gui.T_missile1, t.getPosition()));
				break;
			case 2:
				rockets.emplace_back(new Rocket2(2, 20, t.getDamage(), (int)t.getRotation(), numberOfMonster, gui.T_missile2, t.getPosition()));
				break;
			case 3:
				rockets.emplace_back(new Rocket3(3, 1, t.getDamage(), (int)t.getRotation(), numberOfMonster, gui.T_missile3, t.getPosition()));
				break;
			}
		}
	}
}

//pause
void Game::pause()
{
	gui.takeScreenshot(turrets, monsters, rockets, clicked, cash, kills, level, timeToNextRound, turret1.get(), turret2.get(), turret3.get());
	
	while (!pauseEvents())
	{
		gui.pauseDisplay();
	}
	gui.restoreCursor();
}

bool Game::pauseEvents()
{
	Event e;
	while (gui.pollEvent(e))
	{
		if (e.type == Event::Closed)
		{
			gui.close();
			return true;
		}
		if (e.type == Event::MouseButtonReleased && e.mouseButton.button == Mouse::Left || e.type == Event::KeyReleased)
		{
			if (gui.isButtonResumeClicked() || e.type == Event::KeyReleased && e.key.code == Keyboard::Escape)
			{
				return true;
			}
			else if (gui.isButtonRestartClicked())
			{
				resetGame();
				menu();
				return true;
			}
			else if (gui.isButtonSaveClicked())
			{
				save();
				return true;
			}
			else if (gui.isButtonLoadClicked())
			{
				load();
				return true;
			}
			else if (gui.isButtonExitClicked())
			{
				gui.close();
				return true;
			}
		}
	}
	return false;
}

void Game::save()
{
	fstream file;
	string fileName = "save.txt";
	fileName.insert(fileName.end() - 4, gui.selectedMap() + '0');
	file.open(fileName, ios::out);
	if (file.good())
	{
		file.clear();
		file << timeToNextRound << " " << ifMovingTurret << " " << clicked << " " << level << " " << cash << " " << kills << " " << monsterPictureX << " ";
		file << monsterPictureY << " " << gui.getLinesNumber() << endl;
		file << monsters.size() << endl;

		for (vector<Monster>::iterator it = monsters.begin(); it < monsters.end(); it++)
		{
			it->save(file);
		}
		file << endl << turrets.size() << endl;
		for (vector<Turret>::iterator it = turrets.begin(); it < turrets.end(); it++)
		{
			it->save(file);
		}
		file << endl << rockets.size() << endl;
		for (vector<unique_ptr<Rocket>>::iterator it = rockets.begin(); it < rockets.end(); it++)
		{
			(*it)->save(file);
		}
	}
}

void Game::load()
{
	fstream file;
	string fileName = "save.txt";
	fileName.insert(fileName.end() - 4, gui.selectedMap() + '0');
	file.open(fileName, ios::in);
	if (file.good())
	{
		resetGame();
		int vectorSize;
		file >> timeToNextRound >> ifMovingTurret >> clicked >> level >> cash >> kills >> monsterPictureX >> monsterPictureY;
		file >> vectorSize;				//rozmiar wektora linii
		for (int i = 0; i < vectorSize; i++)
		{
			gui.addLines();
		}
		file >> vectorSize;				//rozmiar wektora potworow
		for (int i = 0; i < vectorSize; i++)
		{
			int level, direction, HP;
			int positionX, positionY;
			int rectLeft, rectTop, rectSize;

			file >> level >> positionX >> positionY >> rectLeft >> rectTop;
			file >> rectSize >> direction >> HP;
			monsters.push_back(Monster(level, gui.fontCalibri, gui.T_monster, Vector2f(positionX, positionY), rectLeft, rectTop, rectSize));
			monsters.back().loadParameters(direction, HP);
		}
		file >> vectorSize;					//rozmiar wektora wiezyczek
		for (int i = 0; i < vectorSize; i++)
		{
			int id, timeToShoot, damage, range, rate, aimAtMonster;
			int positionX, positionY, rotation;

			file >> id >> positionX >> positionY >> timeToShoot >> damage >> range >> rate >> aimAtMonster >> rotation;
			switch (id)
			{
			case 1:
				turrets.push_back(Turret(*turret1));
				turrets.back().loadParameters(positionX, positionY, timeToShoot, damage, range, rate, aimAtMonster, rotation);
				break;
			case 2:
				turrets.push_back(Turret(*turret2));
				turrets.back().loadParameters(positionX, positionY, timeToShoot, damage, range, rate, aimAtMonster, rotation);
				break;
			case 3:
				turrets.push_back(Turret(*turret3));
				turrets.back().loadParameters(positionX, positionY, timeToShoot, damage, range, rate, aimAtMonster, rotation);
				break;
			}
		}
		file >> vectorSize;			//rozmiar wektora pociskow
		for (int i = 0; i < vectorSize; i++)
		{
			int id, speed, damage, numberOfMonster;
			int positionX, positionY, rotation;
			file >> id >> speed >> damage >> rotation >> numberOfMonster >> positionX >> positionY;
			switch (id)
			{
			case 1:
				rockets.emplace_back(new Rocket1(id, 2, damage, rotation, numberOfMonster, gui.T_missile1, Vector2f(positionX, positionY)));
				break;
			case 2:
				rockets.emplace_back(new Rocket2(id, 20, damage, rotation, numberOfMonster, gui.T_missile1, Vector2f(positionX, positionY)));
				break;
			case 3:
				rockets.emplace_back(new Rocket3(id, 1, damage, rotation, numberOfMonster, gui.T_missile1, Vector2f(positionX, positionY)));
				break;
			}
		}
	}
	gui.checkCorners(mapCorners);
}

//menu
void Game::menu()
{
	//ustawianie tel i map do menu
	gui.setMenuGraphics();

	//wyswietlanie calego menu
	while (!menuEvents())
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

bool Game::menuEvents()
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
