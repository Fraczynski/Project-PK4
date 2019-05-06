#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <fstream>
#include "Game.h"
#include "Monster.h"

using namespace std;
using namespace sf;

void Game::menu()
{
	//ustawianie tel
	float scale = 0.4;			//skala pomniejszenia grafik map i tel w menu
	background1.setOrigin(background1.getGlobalBounds().width / 2, background1.getGlobalBounds().height / 2);
	background1.setPosition(width / 4, height / 3);
	background1.setScale(scale, scale);
	background2.setOrigin(background2.getGlobalBounds().width / 2, background2.getGlobalBounds().height / 2);
	background2.setPosition(width * 3 / 4, height / 3);
	background2.setScale(scale, scale);

	//ustawianie map
	map1.setOrigin(map1.getGlobalBounds().width / 2, map1.getGlobalBounds().height / 2);
	map1.setPosition(width / 4, height / 3);
	map1.setScale(scale, scale);
	map2.setOrigin(map2.getGlobalBounds().width / 2, map2.getGlobalBounds().height / 2);
	map2.setPosition(width * 3 / 4, height / 3);
	map2.setScale(scale, scale);
	buttonMap1.reset(new Button(T_button, fontCalibri, map1.getPosition() + Vector2f(0, map1.getGlobalBounds().height), "Select"));
	buttonMap2.reset(new Button(T_button, fontCalibri, map2.getPosition() + Vector2f(0, map2.getGlobalBounds().height), "Select"));

	//wyswietlanie calego menu
	while (!menuEvents())
	{
		window.draw(menuBackground);
		window.draw(background1);
		window.draw(background2);
		window.draw(map1);
		window.draw(map2);
		buttonMap1->display(window);
		buttonMap2->display(window);
		cursor.setPosition(Vector2f(Mouse::getPosition(window)));
		window.draw(cursor);
		window.display();
	}

	//resetowanie ustawien grafik map i tel
	checkCorners();
	map1.setScale(Vector2f(1, 1));
	map1.setPosition(Vector2f(0, 0));
	map1.setOrigin(Vector2f(0, 0));
	map2.setScale(Vector2f(1, 1));
	map2.setPosition(Vector2f(0, 0));
	map2.setOrigin(Vector2f(0, 0));
	background1.setScale(Vector2f(1, 1));
	background1.setPosition(Vector2f(0, 0));
	background1.setOrigin(Vector2f(0, 0));
	background2.setScale(Vector2f(1, 1));
	background2.setPosition(Vector2f(0, 0));
	background2.setOrigin(Vector2f(0, 0));
}

bool Game::menuEvents()
{
	Event e;
	while (window.pollEvent(e))
	{
		if (e.type == Event::Closed)
		{
			window.close();
		}
		if (e.type == Event::MouseButtonReleased && e.mouseButton.button == Mouse::Left || e.type == Event::KeyReleased)
		{
			if (buttonMap1->contains((Vector2f)Mouse::getPosition(window)))
			{
				I_map.loadFromFile("map1.png");
				map = &map1;
				background = &background1;
				endLinesMap = &endLinesMap1;
				return true;
			}
			else if (buttonMap2->contains((Vector2f)Mouse::getPosition(window)))
			{
				I_map.loadFromFile("map2.png");
				map = &map2;
				background = &background2;
				endLinesMap = &endLinesMap2;
				return true;
			}
		}
	}
	return false;
}

//logika gry
bool Game::isPlayed()
{
	return window.isOpen();
}

void Game::resetGame()
{
	timeToNextRound = 30;		//pozostaly czas do kolejnej rundy
	ifMovingTurret = 0;			//czy przenoszona aktualnie jest wiezyczka: 0 - nie; 1 - tak
	clicked = -1;				//numer zaznaczonej wiezyczki: -1 - brak zaznaczonej
	level = 0;					//numer aktualnego poziomu
	cash = 2000000;					//poczatkowa ilosc pieniedzy
	kills = 0;					//licznik zabitych potworow
	monsterPictureX = 0;		//wspolrzedna x aktualnego sprite'a potwora
	monsterPictureY = 0;		//wspolrzedna y aktualnego sprite'a potwora
	texts->updateInfo();

	//czyszczenie wszystkich wektorow
	monsters.clear();
	turrets.clear();
	rockets.clear();
	lines.clear();
	mapCorners.clear();
	//resetowanie sklepu
	resetTurrets();

	//wywolanie menu
	menu();

	//for (int i = 0; i < 10; i++) { monsters.push_back(Monster(level, fontCalibri, T_monster, Vector2f(709, 300 - i * 30), monsterPictureX, monsterPictureY, monsterSize)); monsters.push_back(Monster(level, fontCalibri, T_monster, Vector2f(132, 400 - i * 30), monsterPictureX, monsterPictureY, monsterSize));}
}

void Game::resetTurrets()
{
	cursor.setTexture(T_cursor1);
	cursor.setOrigin(0, 0);
	ifMovingTurret = 0;
	turret1->setPosition(vectorTurret1);
	turret2->setPosition(vectorTurret2);
	turret3->setPosition(vectorTurret3);
	circle.setPosition(0, 0);
	circle.setRadius(0);
	texts->updateInfo();
}

void Game::events()
{
	Event e;
	while (window.pollEvent(e))
	{
		if (e.type == Event::Closed)
		{
			window.close();
		}
		if (e.type == Event::KeyReleased && e.key.code == Keyboard::Escape)
		{
			pause();
		}
		if (e.type == Event::MouseButtonReleased && e.mouseButton.button == Mouse::Left)
		{
			leftButtonReleased();
		}
		if (e.type == Event::MouseButtonReleased && e.mouseButton.button == Mouse::Right)
		{
			resetTurrets();
		}
	}
}

void Game::pause()
{
	mousePosition = Mouse::getPosition(window);
	Mouse::setPosition(Vector2i(0, -32), window);
	display(); display(); display();
	T_screenShot.update(window);
	screenShot.setTexture(T_screenShot);
	screenShot.setColor(Color(110, 110, 110));
	Mouse::setPosition(mousePosition, window);
	Sprite cursorTmp(T_cursor1);

	while (1)
	{
		cursorTmp.setPosition(Vector2f(Mouse::getPosition(window)));
		pauseMenu(cursorTmp);
		if (buttonEvents())
		{
			return;
		}
	}
	Mouse::setPosition(mousePosition, window);
	cursor = cursorTmp;
}

bool Game::buttonEvents()
{
	Event e;
	while (window.pollEvent(e))
	{
		if (e.type == Event::Closed)
		{
			window.close();
		}
		if (e.type == Event::MouseButtonReleased && e.mouseButton.button == Mouse::Left || e.type == Event::KeyReleased)
		{
			if (buttonResume->contains((Vector2f)Mouse::getPosition(window)) || e.type == Event::KeyReleased && e.key.code == Keyboard::Escape)
			{
				return true;
			}
			else if (buttonRestart->contains((Vector2f)Mouse::getPosition(window)))
			{
				resetGame();
				return true;
			}
			else if (buttonSave->contains((Vector2f)Mouse::getPosition(window)))
			{
				save();
				return true;
			}
			else if (buttonLoad->contains((Vector2f)Mouse::getPosition(window)))
			{
				load();
				return true;
			}
			else if (buttonExit->contains((Vector2f)Mouse::getPosition(window)))
			{
				window.close();
			}
		}
	}
	return false;
}

void Game::leftButtonReleased()
{
	Vector2i position = Mouse::getPosition(window);
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
		turret1->setPosition((Vector2f)Mouse::getPosition(window));
		updateCircle((Vector2f)Mouse::getPosition(window), turret1->getRange());
		break;
	case 2:
		turret2->setPosition((Vector2f)Mouse::getPosition(window));
		updateCircle((Vector2f)Mouse::getPosition(window), turret2->getRange());
		break;
	case 3:
		turret3->setPosition((Vector2f)Mouse::getPosition(window));
		updateCircle((Vector2f)Mouse::getPosition(window), turret3->getRange());
		break;
	}
}

bool Game::notMovingTurret()
{
	if (turret1->contains((Vector2f)Mouse::getPosition(window)))
	{
		cursor.setTexture(T_cursor2);
		cursor.setOrigin(cursor.getGlobalBounds().width / 2, cursor.getGlobalBounds().height / 2);
		ifMovingTurret = 1;
		texts->updateInfo(*turret1);
		return true;
	}
	else if (turret2->contains((Vector2f)Mouse::getPosition(window)))
	{
		cursor.setTexture(T_cursor2);
		cursor.setOrigin(cursor.getGlobalBounds().width / 2, cursor.getGlobalBounds().height / 2);
		ifMovingTurret = 2;
		texts->updateInfo(*turret2);
		return true;
	}
	else if (turret3->contains((Vector2f)Mouse::getPosition(window)))
	{
		cursor.setTexture(T_cursor2);
		cursor.setOrigin(cursor.getGlobalBounds().width / 2, cursor.getGlobalBounds().height / 2);
		ifMovingTurret = 3;
		texts->updateInfo(*turret3);
		return true;
	}
	return false;
}

bool Game::turretClicked()
{
	for (unsigned i = 0; i < turrets.size(); i++)
	{
		if (turrets[i].contains((Vector2f)Mouse::getPosition(window)))
		{
			clicked = i;
			updateCircle((turrets.begin() + clicked)->getPosition(), (turrets.begin() + clicked)->getRange());
			texts->updateInfo(*(turrets.begin() + clicked));
			return true;
		}
	}
	clicked = -1;
	updateCircle(Vector2f(0, 0), 0);
	texts->updateInfo();
	return false;
}

void Game::upgradeTurrets()
{
	switch (texts->upgradingTextClicked(window))
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
	updateCircle((turrets.begin() + clicked)->getPosition(), (turrets.begin() + clicked)->getRange());
	texts->updateInfo(*(turrets.begin() + clicked));
}

void Game::updateCircle(const Vector2f & position, const int & range)
{
	circle.setPosition(position);
	circle.setRadius((float)range);
	circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
}

void Game::updateClock()
{
	arrow.setRotation(float(timeToNextRound / 3.33));
}

void Game::move_monsters()
{
	for (unsigned i = 0; i < monsters.size(); i++)
	{
		if (monsters[i].move(mapCorners))
		{
			addLines();
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
			monsters.push_back(Monster(level, fontCalibri, T_monster, Vector2f(920, -60 * (float)i), monsterPictureX, monsterPictureY, monsterSize));
		}
		monsterPictureX += monsterSize;
		if (monsterPictureX >= (int)T_monster.getSize().x)
		{
			monsterPictureX = 0;
			monsterPictureY += monsterSize;
			if (monsterPictureY >= (int)T_monster.getSize().y)
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

bool Game::checkPixel(const int & x, const int & y)
{
	if (((int)I_map.getPixel(x, y).r >= 143 && (int)I_map.getPixel(x, y).r <= 149 && (int)I_map.getPixel(x, y).g >= 205 &&
		(int)I_map.getPixel(x, y).g <= 211 && (int)I_map.getPixel(x, y).b >= 77 && (int)I_map.getPixel(x, y).b <= 83) ||
		((int)I_map.getPixel(x, y).r > 252 && (int)I_map.getPixel(x, y).g < 5 && (int)I_map.getPixel(x, y).b < 5))
	{
		return false;
	}
	return true;
}

void Game::addLines()
{
	lines.push_back(Sprite(T_line));
	lines.back().setOrigin(lines.back().getGlobalBounds().width / 2, lines.back().getGlobalBounds().height / 2);
	lines.back().setPosition(endLinesMap->x + 20 * (float)lines.size(), endLinesMap->y);
}

void Game::save()
{
	fstream file;
	file.open("save.txt", ios::out);
	if (file.good())
	{
		file.clear();
		file << timeToNextRound << " " << ifMovingTurret << " " << clicked << " " << level << " " << cash << " " << kills << " " << monsterPictureX << " ";
		file << monsterPictureY << " " << lines.size() << endl;
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
	else
	{
		Sleep(3000);
	}
}

bool Game::checkPlace(const Vector2f & position, const int & w, const int & h)
{
	int i;
	if (position.y + w / 2 + 3 <= 624)
	{
		for (
			(position.y - w / 2 - 3 >= 0) ? (i = (int)position.y - w / 2 - 3) : i = 0; i < position.y + w / 2 + 3 && i < height; i++)
		{
			if (!checkPixel((int)position.x, i) || !checkPixel((int)position.x + w / 2 - 1, i))
			{
				return false;
			}
		}
		for (((int)position.x - w / 2 - 3 >= 0) ? (i = (int)position.x - w / 2 - 3) : (i = 0); i < (int)position.x + w / 2 + 3 && i < width; i++)
		{
			if (!checkPixel(i, (int)position.y) || !checkPixel(i, (int)position.y + w / 2 - 1))
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

void Game::load()
{
	fstream file;
	file.open("save.txt", ios::in);
	if (file.good())
	{
		resetGame();
		int vectorSize;
		int tmp;
		file >> timeToNextRound >> ifMovingTurret >> clicked >> level >> cash >> kills >> monsterPictureX >> monsterPictureY;
		file >> vectorSize;				//rozmiar wektora linii
		for (int i = 0; i < vectorSize; i++)
		{
			addLines();
		}
		file >> vectorSize;				//rozmiar wektora potworow
		for (int i = 0; i < vectorSize; i++)
		{
			int level;
			float positionX, positionY;
			int rectLeft, rectTop, rectSize;
			int direction, HP;

			file >> level >> positionX >> positionY >> rectLeft >> rectTop;
			file >> rectSize >> direction >> HP;
			monsters.push_back(Monster(level, fontCalibri, T_monster, Vector2f(positionX, positionY), rectLeft, rectTop, rectSize));
			monsters.back().loadParameters(direction, HP);
		}
		file >> vectorSize;					//rozmiar wektora wiezyczek
		for (int i = 0; i < vectorSize; i++)
		{
			int id, timeToShoot, damage, range, rate, aimAtMonster;
			float positionX, positionY;
			float rotation;

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
			float positionX, positionY;
			float rotation;
			file >> id >> speed >> damage >> rotation >> numberOfMonster >> positionX >> positionY;
			switch (id)
			{
			case 1:
				rockets.emplace_back(new Rocket1(1, 2, damage, (int)rotation, tmp, T_missile1, Vector2f(positionX, positionY)));
				break;
			case 2:
				rockets.emplace_back(new Rocket2(2, 20, damage, (int)rotation, tmp, T_missile1, Vector2f(positionX, positionY)));
				break;
			case 3:
				rockets.emplace_back(new Rocket3(3, 1, damage, (int)rotation, tmp, T_missile1, Vector2f(positionX, positionY)));
				break;
			}
		}
	}
	else
	{
		Sleep(3000);
	}
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
				rockets.emplace_back(new Rocket1(1, 2, t.getDamage(), (int)t.getRotation(), numberOfMonster, T_missile1, t.getPosition()));
				break;
			case 2:
				rockets.emplace_back(new Rocket2(2, 20, t.getDamage(), (int)t.getRotation(), numberOfMonster, T_missile2, t.getPosition()));
				break;
			case 3:
				rockets.emplace_back(new Rocket3(3, 1, t.getDamage(), (int)t.getRotation(), numberOfMonster, T_missile3, t.getPosition()));
				break;
			}
		}
	}
}

void Game::end()
{
	if (endAnimation())
	{
		window.close();
	}
}

//GUI
void Game::loadGraphics()
{
	//tworzenie okna aplikacji
	window.create(VideoMode(width, height, 32), "Onslaught");
	window.clear(Color(55, 0, 0));
	window.setActive(true);
	window.setFramerateLimit(60);
	window.setIcon(icon.width, icon.height, icon.pixel_data);
	window.setMouseCursorVisible(false);
	//window.setMouseCursorGrabbed(true);

	//wczytywanie grafik
	try
	{
		if (!fontCalibri.loadFromFile("calibri.ttf") || !fontTimesNewRoman.loadFromFile("times.ttf") || !T_background.loadFromFile("background1.png") || 
			!T_map1.loadFromFile("map1.png") || !T_map2.loadFromFile("map2.png") || !T_bar.loadFromFile("bar.png") || !T_turret1.loadFromFile("turret1.png") || 
			!T_turret2.loadFromFile("turret2.png") ||
			!T_turret3.loadFromFile("turret3.png") || !T_monster.loadFromFile("monster.png") || !T_cursor1.loadFromFile("cursor1.png") || !T_cursor2.loadFromFile("cursor2.png") ||
			!T_missile1.loadFromFile("missile1.png") || !T_missile2.loadFromFile("missile2.png") || !T_missile3.loadFromFile("missile3.png") || !T_arrow.loadFromFile("arrow.png") ||
			!T_line.loadFromFile("line.png") || !T_gameOver.loadFromFile("end.png") || !T_button.loadFromFile("button.png") || !T_background.loadFromFile("background.png") || 
			!T_background1.loadFromFile("background1.png") || !T_background2.loadFromFile("background2.png") ||
			!T_map1.loadFromFile("map1.png") || !T_map2.loadFromFile("map2.png"))
		{
			throw - 1;
		}
	}
	catch (int)
	{
		//brak niezbednych grafik
		window.clear(Color::Red);
		Text error("Blad wczytywania plikow!", fontCalibri, 48);
		error.setFillColor(Color::White);
		error.setOrigin(error.getGlobalBounds().width / 2, error.getGlobalBounds().height / 2);
		error.setPosition(width / 2, height / 2);
		window.draw(error);
		window.display();
		Sleep(3000);
		window.close();
	}

	//wygladzenie wszystkich tekstur
	T_background.setSmooth(true);
	T_background1.setSmooth(true);
	T_background2.setSmooth(true);
	T_map1.setSmooth(true);
	T_map2.setSmooth(true);
	T_bar.setSmooth(true);
	T_arrow.setSmooth(true);
	T_line.setSmooth(true);
	T_gameOver.setSmooth(true);
	T_button.setSmooth(true);
	T_turret1.setSmooth(true);
	T_turret2.setSmooth(true);
	T_turret3.setSmooth(true);
	T_monster.setSmooth(true);
	T_missile1.setSmooth(true);
	T_missile2.setSmooth(true);
	T_missile3.setSmooth(true);
	T_cursor1.setSmooth(true);
	T_cursor2.setSmooth(true);
	
	//ustawienie dolnego paska gry
	bar.setTexture(T_bar);
	bar.setPosition(0, 625);

	//ustawienie wskazowki zegara
	arrow.setTexture(T_arrow);
	arrow.setPosition(957, 657);
	arrow.setOrigin(arrow.getGlobalBounds().width / 2, arrow.getGlobalBounds().height - 3);
	
	//ustawienie grafiki konca gry i tekstury na screenshot
	T_screenShot.create(width, height);
	gameOver.setTexture(T_gameOver);
	gameOver.setOrigin(gameOver.getGlobalBounds().width / 2, gameOver.getGlobalBounds().height / 2);
	gameOver.setPosition(width / 2, height / 2);
	gameOver.setScale(5, 5);

	//ustawienie kola zaznaczajacego zasieg wiezyczki
	circle.setFillColor(Color(0, 0, 0, 130));
	circle.setPointCount(50);
	circle.setPosition(0, 0);

	//ustawienie spritow tel i map
	menuBackground.setTexture(T_background);
	background1.setTexture(T_background1);
	background2.setTexture(T_background2);
	map1.setTexture(T_map1);
	map2.setTexture(T_map2);

	//ustawienie przyciskow pause
	buttonResume.reset(new Button(T_button, fontTimesNewRoman, Vector2f(width / 2, 2 * height / 8), "RESUME"));
	buttonRestart.reset(new Button(T_button, fontTimesNewRoman, Vector2f(width / 2, 3 * height / 8), "RESTART"));
	buttonSave.reset(new Button(T_button, fontTimesNewRoman, Vector2f(width / 2, 4 * height / 8), "SAVE"));
	buttonLoad.reset(new Button(T_button, fontTimesNewRoman, Vector2f(width / 2, 5 * height / 8), "LOAD"));
	buttonExit.reset(new Button(T_button, fontTimesNewRoman, Vector2f(width / 2, 6 * height / 8), "EXIT"));

	//ustawienie wiezyczek w menu
	turret1.reset(new Turret(1, T_turret1, vectorTurret1));
	turret2.reset(new Turret(2, T_turret2, vectorTurret2));
	turret3.reset(new Turret(3, T_turret3, vectorTurret3));

	//ustawienie kursora
	cursor.setTexture(T_cursor2);
	cursor.setTexture(T_cursor1);

	//ustawienie tekstow wyswietlanych na pasku gry
	texts.reset(new Texts(fontCalibri, Vector2f(vectorTurret1.x, vectorTurret1.y - 5), Vector2f(vectorTurret2.x, vectorTurret2.y - 5), Vector2f(vectorTurret3.x, vectorTurret3.y - 5), turret1, turret2, turret3));
	texts->updateInfo();
}

void Game::display()
{
	window.clear(Color(255, 0, 0));
	window.draw(*background);
	window.draw(*map);

	for (vector<Sprite>::iterator it = lines.begin(); it < lines.end(); it++)
	{
		window.draw(*it);
	}
	for (vector<Monster>::iterator it = monsters.begin(); it < monsters.end(); it++)
	{
		it->display(window);
	}
	for (vector<Turret>::iterator it = turrets.begin(); it < turrets.end(); it++)
	{
		it->display(window);
	}
	if (clicked >= 0)
	{
		turrets[clicked].display(window);
	}
	window.draw(circle);
	for (vector<unique_ptr<Rocket>>::iterator it = rockets.begin(); it < rockets.end(); it++)
	{
		(*it)->display(window);
	}
	window.draw(bar);
	window.draw(arrow);
	texts->display(cash, kills, level, window);

	turret1->display(window);
	turret2->display(window);
	turret3->display(window);
	cursor.setPosition(Vector2f(Mouse::getPosition(window)));
	window.draw(cursor);

	window.display();
	timeToNextRound--;
}

void Game::pauseMenu(const Sprite & cursorTmp)
{
	window.draw(screenShot);
	buttonResume->display(window);
	buttonRestart->display(window);
	buttonSave->display(window);
	buttonLoad->display(window);
	buttonExit->display(window);
	window.draw(cursorTmp);
	window.display();
}

bool Game::endAnimation()
{
	if (lines.size() == 10)
	{
		T_screenShot.update(window);
		screenShot.setTexture(T_screenShot);
		for (int i = 0; i < 60; i++)
		{
			gameOver.scale(0.98 + i / 1000, 0.98 + i / 1000);
			window.draw(screenShot);
			window.draw(gameOver);
			window.display();
			Sleep(15);
		}
		Sleep(3000);
		return true;
	}
	return false;
}

void Game::checkCorners()
{
	int direction = 0;
	int positionX = 920;
	int positionY = 20;
	while (I_map.getPixel(positionX, positionY).r != 255)
	{
		//poruszanie potworami w odpowiednim kierunku az do napotkania zakretu
		switch (direction)
		{
		case 0:
			while (I_map.getPixel(positionX, positionY + 20).a > 200 && I_map.getPixel(positionX, positionY).r != 255)
			{
				positionY++;
			}
			break;
		case 1:
			while (I_map.getPixel(positionX - 20, positionY).a > 200 && I_map.getPixel(positionX, positionY).r != 255)
			{
				positionX--;
			}
			break;
		case 2:
			while (I_map.getPixel(positionX, positionY - 20).a > 200 && I_map.getPixel(positionX, positionY).r != 255)
			{
				positionY--;
			}
			break;
		case 3:
			while (I_map.getPixel(positionX + 20, positionY).a > 200 && I_map.getPixel(positionX, positionY).r != 255)
			{
				positionX++;
			}
			break;
		}

		//sprawdzanie, w ktora strone zakreca sciezka i dodanie odpowiedniego punktu z kierunkiem do wektora punktow 
		if (I_map.getPixel(positionX, positionY).r > 250)
		{
			direction = 5;
			mapCorners.push_back(Map{ Vector2f(positionX, positionY), direction });
		}
		else if (I_map.getPixel(positionX, positionY + 25).a > 200 && direction != 2)
		{
			direction = 0;
			mapCorners.push_back(Map{ Vector2f(positionX, positionY), direction });
		}
		else if (I_map.getPixel(positionX - 25, positionY).a > 200 && direction != 3)
		{
			direction = 1;
			mapCorners.push_back(Map{ Vector2f(positionX, positionY), direction });
		}
		else if (I_map.getPixel(positionX, positionY - 25).a > 200 && direction != 0)
		{
			direction = 2;
			mapCorners.push_back(Map{ Vector2f(positionX, positionY), direction });
		}
		else if (I_map.getPixel(positionX + 25, positionY).a > 200 && direction != 1)
		{
			direction = 3;
			mapCorners.push_back(Map{ Vector2f(positionX, positionY), direction });
		}
	}
}