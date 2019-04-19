#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <fstream>
#include "Game.h"
#include "Monster.h"
//#include <fstream>

using namespace std;
using namespace sf;

void Game::gameLoop()
{
	loadGraphics();
	resetGame();
	display();

	/*for (int i = 0; i < 10; i++)
	{
		monsters.push_back(Monster(level, font, T_monster1, Vector2f(709, 300 - i * 30), monsterPictureX, monsterPictureY, monsterSize));
	}*/
	while (window.isOpen())				//petla wykonujaca sie dopoki nie zostanie zakonczona gra
	{
		events();
		move_monsters();
		add_monsters(timeToNextRound);
		rotate_turrets();
		shoot();
		move_missiles();
		moveTurret();
		updateClock();
		display();
		end();
	}
}

void Game::loadGraphics()
{
	window.create(VideoMode(width, height, 32), "Onslaught");
	window.clear(Color(255, 0, 0));
	window.setActive(true);
	window.setFramerateLimit(60);
	window.setIcon(icon.width, icon.height, icon.pixel_data);
	window.setMouseCursorVisible(false);
	//window.setMouseCursorGrabbed(true);

	try
	{
		if (!T_background.loadFromFile("background.png") || !I_map1.loadFromFile("map1.png") || !T_map1.loadFromFile("map1.png") || !T_bar.loadFromFile("bar.png") || 
			!T_turret1.loadFromFile("turret1.png") || !T_turret2.loadFromFile("turret2.png") ||	!T_turret3.loadFromFile("turret3.png") || !I_monster1.loadFromFile("monster1.png") || 
			!T_cursor1.loadFromFile("cursor1.png") || !T_cursor2.loadFromFile("cursor2.png") || !T_missile1.loadFromFile("missile1.png") || 
			!T_missile2.loadFromFile("missile2.png") || !T_missile3.loadFromFile("missile3.png") || !T_arrow.loadFromFile("arrow.png") || !font.loadFromFile("calibri.ttf") || 
			!T_line.loadFromFile("line.png") || !T_gameOver.loadFromFile("end.png") || !T_buttonResume.loadFromFile("resume.png") || !T_buttonRestart.loadFromFile("restart.png") ||
			!T_buttonSave.loadFromFile("save.png") || !T_buttonLoad.loadFromFile("load.png") || !T_buttonExit.loadFromFile("exit.png"))
		{
			throw - 1;
		}
	}
	catch (int)
	{
		cout << "Blad wczytywania plikow!";
		Sleep(5000);
		window.close();
	}
	T_background.setSmooth(true);
	background.setTexture(T_background);
	T_map1.setSmooth(true);
	map1.setTexture(T_map1);

	T_bar.setSmooth(true);
	bar.setTexture(T_bar);
	bar.setPosition(0, 625);

	T_arrow.setSmooth(true);
	arrow.setTexture(T_arrow);
	arrow.setPosition(957, 657);
	arrow.setOrigin(arrow.getGlobalBounds().width / 2, arrow.getGlobalBounds().height - 3);

	T_line.setSmooth(true);

	T_screenShot.create(width, height);
	T_gameOver.setSmooth(true);
	gameOver.setTexture(T_gameOver);
	gameOver.setOrigin(gameOver.getGlobalBounds().width / 2, gameOver.getGlobalBounds().height / 2);
	gameOver.setPosition(width / 2, map1.getGlobalBounds().height / 2);
	gameOver.setScale(5, 5);

	circle.setFillColor(Color(0, 0, 0, 130));
	circle.setPointCount(50);
	circle.setPosition(0, 0);

	T_buttonResume.setSmooth(true);
	T_buttonRestart.setSmooth(true);
	T_buttonSave.setSmooth(true);
	T_buttonLoad.setSmooth(true);
	T_buttonExit.setSmooth(true);
	buttonResume.setTexture(T_buttonResume);
	buttonRestart.setTexture(T_buttonRestart);
	buttonSave.setTexture(T_buttonSave);
	buttonLoad.setTexture(T_buttonLoad);
	buttonExit.setTexture(T_buttonExit);
	buttonResume.setOrigin(buttonResume.getGlobalBounds().width / 2, buttonResume.getGlobalBounds().height / 2);
	buttonRestart.setOrigin(buttonRestart.getGlobalBounds().width / 2, buttonRestart.getGlobalBounds().height / 2);
	buttonSave.setOrigin(buttonSave.getGlobalBounds().width / 2, buttonSave.getGlobalBounds().height / 2);
	buttonLoad.setOrigin(buttonSave.getGlobalBounds().width / 2, buttonSave.getGlobalBounds().height / 2);
	buttonExit.setOrigin(buttonExit.getGlobalBounds().width / 2, buttonExit.getGlobalBounds().height / 2);
	buttonResume.setPosition(width / 2, 2 * height / 8);
	buttonRestart.setPosition(width / 2, 3 * height / 8);
	buttonSave.setPosition(width / 2, 4 * height / 8);
	buttonLoad.setPosition(width / 2, 5 * height / 8);
	buttonExit.setPosition(width / 2, 6 * height / 8);

	T_turret1.setSmooth(true);
	T_turret2.setSmooth(true);
	T_turret3.setSmooth(true);
	turret1 = new Turret(1, T_turret1, vectorTurret1);
	turret2 = new Turret(2, T_turret2, vectorTurret2);
	turret3 = new Turret(3, T_turret3, vectorTurret3);

	//T_monster1.setSmooth(true);
	T_missile1.setSmooth(true);
	T_missile2.setSmooth(true);
	T_missile3.setSmooth(true);

	T_cursor1.setSmooth(true);
	T_cursor2.setSmooth(true);
	cursor.setTexture(T_cursor2);
	cursor.setTexture(T_cursor1);

	texts = new Texts(font, Vector2f(vectorTurret1.x, vectorTurret1.y - 5), Vector2f(vectorTurret2.x, vectorTurret2.y - 5), Vector2f(vectorTurret3.x, vectorTurret3.y - 5), turret1, turret2, turret3);
	texts->updateInfo();
}

void Game::resetGame()
{
	timeToNextRound = 30;		//pozostaly czas do kolejnej rundy
	ifMovingTurret = 0;			//czy przenoszona aktualnie jest wiezyczka: 0 - nie; 1 - tak
	clicked = -1;				//numer zaznaczonej wiezyczki: -1 - brak zaznaczonej
	level = 10;					//numer aktualnego poziomu
	cash = 100000;					//poczatkowa ilosc pieniedzy
	kills = 0;					//licznik zabitych potworow
	monsterPictureX = 0;		//wspolrzedna x aktualnego sprite'a potwora
	monsterPictureY = 0;		//wspolrzedna y aktualnego sprite'a potwora
	texts->updateInfo();

	monsters.clear();
	turrets.clear();
	for (int i = 0; i < rockets.size(); i++)
	{
		delete rockets[i];
		rockets.erase(rockets.begin() + i);
		i--;
	}
	lines.clear();
	resetTurrets();
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

void Game::display()
{
	window.clear(Color(255, 0, 0));
	window.draw(background);
	window.draw(map1);
		
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
	for (vector<Rocket *>::iterator it = rockets.begin(); it < rockets.end(); it++)
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

void Game::events()
{
	Event e;
	while (window.pollEvent(e))
	{
		if (e.type == Event::Closed)
		{
			exit();
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
		window.draw(screenShot);
		window.draw(buttonResume);
		window.draw(buttonRestart);
		window.draw(buttonSave);
		window.draw(buttonLoad);
		window.draw(buttonExit);
		cursorTmp.setPosition(Vector2f(Mouse::getPosition(window)));
		window.draw(cursorTmp);
		window.display();
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
			exit();
		}
		if (e.type == Event::MouseButtonReleased && e.mouseButton.button == Mouse::Left || e.type == Event::KeyReleased)
		{
			if (buttonResume.getGlobalBounds().contains((Vector2f)Mouse::getPosition(window)) || e.type == Event::KeyReleased && e.key.code == Keyboard::Escape)
			{
				return true;
			}
			else if (buttonRestart.getGlobalBounds().contains((Vector2f)Mouse::getPosition(window)))
			{
				resetGame();
				return true;
			}
			else if (buttonSave.getGlobalBounds().contains((Vector2f)Mouse::getPosition(window)))
			{
				save();
				return true;
			}
			else if (buttonLoad.getGlobalBounds().contains((Vector2f)Mouse::getPosition(window)))
			{
				load();
				return true;
			}
			else if (buttonExit.getGlobalBounds().contains((Vector2f)Mouse::getPosition(window)))
			{
				exit();
			}
		}
	}
}

void Game::leftButtonReleased()
{
	Vector2i position = Mouse::getPosition(window);
	if (position.y >= 625)			//tu wstawic ulepszanie wiezyczek
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
		else if (clicked >= 0 && clicked < turrets.size())
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
	circle.setRadius(range);
	circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
}

void Game::updateClock()
{
	arrow.setRotation(timeToNextRound / 3.33);
}

void Game::move_monsters()
{
	for (unsigned i = 0; i < monsters.size(); i++)
	{
		if (monsters[i].move(cornersMap1))
		{
			addLines();
			monsters.erase(monsters.begin() + i);
			i--;
		}
	}
}

void Game::add_monsters(int)
{
	if (timeToNextRound < 0)
	{
		timeToNextRound = roundTime;
		level++;
		T_monster1.loadFromImage(I_monster1);//, IntRect(monsterPictureX, monsterPictureY, monsterSize, monsterSize));
		for (int i = 0; i < 10; i++)
		{
			monsters.push_back(Monster(level, font, T_monster1, Vector2f(920, -60 * i), monsterPictureX, monsterPictureY, monsterSize));
		}
		monsterPictureX += monsterSize;
		if (monsterPictureX >= I_monster1.getSize().x)
		{
			monsterPictureX = 0;
			monsterPictureY += monsterSize;
			if (monsterPictureY >= I_monster1.getSize().y)
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
	for (int i = 0; i < rockets.size(); i++)
	{
		if (rockets[i]->specialAbilities(monsters, cash, kills))
		{
			delete rockets[i];
			rockets.erase(rockets.begin() + i);
			i--;
		}
	}
}

bool Game::checkPixel(const int & x, const int & y)
{
	if (((int)I_map1.getPixel(x, y).r >= 143 && (int)I_map1.getPixel(x, y).r <= 149 && (int)I_map1.getPixel(x, y).g >= 205 &&
		(int)I_map1.getPixel(x, y).g <= 211 && (int)I_map1.getPixel(x, y).b >= 77 && (int)I_map1.getPixel(x, y).b <= 83) ||
		((int)I_map1.getPixel(x, y).r > 252 && (int)I_map1.getPixel(x, y).g < 5 && (int)I_map1.getPixel(x, y).b < 5))
	{
		return false;
	}
	return true;
}

void Game::addLines()
{
	lines.push_back(Sprite(T_line));
	lines.back().setOrigin(lines.back().getGlobalBounds().width / 2, lines.back().getGlobalBounds().height / 2);
	lines.back().setPosition(343 + 20 * lines.size(), 272);
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
		for (vector<Rocket *>::iterator it = rockets.begin(); it < rockets.end(); it++)
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
		for ((position.y - w / 2 - 3 >= 0) ? (i = position.y - w / 2 - 3) : i = 0; i < position.y + w / 2 + 3 && i < height; i++)
		{
			if (!checkPixel(position.x, i) || !checkPixel(position.x + w / 2 - 1, i))
			{
				return false;
			}
		}
		for ((position.x - w / 2 - 3 >= 0) ? (i = position.x - w / 2 - 3) : (i = 0); i < position.x + w / 2 + 3 && i < width; i++)
		{
			if (!checkPixel(i, position.y) || !checkPixel(i, position.y + w / 2 - 1))
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
			float rotation;
			int direction, HP;

			T_monster1.loadFromImage(I_monster1);
			file >> level >> positionX >> positionY >> rectLeft >> rectTop;
			file >> rectSize >> direction >> HP;
			monsters.push_back(Monster(level, font, T_monster1, Vector2f(positionX, positionY), rectLeft, rectTop, rectSize));
			monsters.back().loadParameters(direction, HP);
		}
		file >> vectorSize;					//rozmiar wektora wiezyczek
		for (int i = 0; i < vectorSize; i++)
		{
			int id, price, timeToShoot, damage, range, rate, aimAtMonster;
			float positionX, positionY;
			float rotation;

			T_monster1.loadFromImage(I_monster1);
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
				rockets.push_back(new Rocket1(1, 2, damage, rotation, tmp, T_missile1, Vector2f(positionX, positionY)));
				break;
			case 2:
				rockets.push_back(new Rocket2(2, 20, damage, rotation, tmp, T_missile1, Vector2f(positionX, positionY)));
				break;
			case 3:
				rockets.push_back(new Rocket3(3, 1, damage, rotation, tmp, T_missile1, Vector2f(positionX, positionY)));
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
		if (numberOfMonster >= 0 && numberOfMonster < monsters.size())
		{
			switch (t.getID())
			{
			case 1:
				rockets.push_back(new Rocket1(1, 2, t.getDamage(), t.getRotation(), numberOfMonster, T_missile1, t.getPosition()));
				break;
			case 2:
				rockets.push_back(new Rocket2(2, 20, t.getDamage(), t.getRotation(), numberOfMonster, T_missile2, t.getPosition()));
				break;
			case 3:
				rockets.push_back(new Rocket3(3, 1, t.getDamage(), t.getRotation(), numberOfMonster, T_missile3, t.getPosition()));
				break;
			}
		}
	}
}

void Game::end()
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
		exit();
	}
}

void Game::exit()
{
	for (int i = 0; i < rockets.size(); i++)
	{
		delete rockets[i];
		rockets.erase(rockets.begin() + i);
		i--;
	}
	delete turret1;
	delete turret2;
	delete turret3;
	window.close();
	std::exit(0);
}
