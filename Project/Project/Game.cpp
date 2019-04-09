#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Game.h"
#include "Monster.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
using namespace sf;

void Game::gameLoop(int argc, char * argv[])
{
	window.create(VideoMode(width, height, 32), "Onslaught");
	window.clear(Color(255, 0, 0));
	window.setActive(true);
	window.setFramerateLimit(60);
	window.setIcon(icon.width, icon.height, icon.pixel_data);
	window.setMouseCursorVisible(false);
	//window.setMouseCursorGrabbed(true);

	loadGraphics();
	display();

	/*for (int i = 0; i < 10; i++)
	{
		monsters.push_back(Monster(1, font, T_monster1, Vector2f(709, 300 - i * 30)));				//usunac po testach
	}*/
	while (window.isOpen())				//petla wykonujaca sie dopoki nie zostanie zakonczona gra
	{
		events();
		move_monsters();
		add_monsters(timeToNextRound);
		rotate_turrets();
		shoot();
		move_rockets();
		updateClock();
		display();
		end();
	}
}

void Game::loadGraphics()
{
	try
	{
		if (!I_map.loadFromFile("map1.png") || !T_map.loadFromFile("map1.png") || !T_bar.loadFromFile("bar.png") || !T_turret1.loadFromFile("turret1.png") || !T_turret2.loadFromFile("turret2.png") ||
			!T_turret3.loadFromFile("turret3.png") || !T_monster1.loadFromFile("monster1.png") || !T_monster2.loadFromFile("monster2.png") || 
			!T_cursor1.loadFromFile("cursor1.png") || !T_cursor2.loadFromFile("cursor2.png") ||
			!T_cursor3.loadFromFile("cursor3.png") || !T_cursor4.loadFromFile("cursor4.png") || !T_missile1.loadFromFile("missile1.png") || !T_missile2.loadFromFile("missile2.png") ||
			!T_missile3.loadFromFile("missile3.png") || !T_arrow.loadFromFile("arrow.png") || !font.loadFromFile("calibri.ttf") || !T_line.loadFromFile("line.png") ||
			!T_gameOver.loadFromFile("end.png"))
		{
			throw -1;
		}
	}
	catch(int)
	{
		cout << "Blad wczytywania plikow!";
		Sleep(5000);
		window.close();
	}
	T_map.setSmooth(true);
	map.setTexture(T_map);

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
	gameOver.setPosition(width / 2, map.getGlobalBounds().height / 2);
	gameOver.setScale(5, 5);

	//circle.setFillColor(Color(255, 127, 39, 150));		//pomaranczowy
	circle.setFillColor(Color(0, 0, 0, 130));
	circle.setPointCount(50);
	circle.setRadius(0);				//skasowac po dodaniu sprawdzania zasiegu wiezyczki
	circle.setPosition(0, 0);

	T_turret1.setSmooth(true);
	T_turret2.setSmooth(true);
	T_turret3.setSmooth(true);
	turret1 = new Turret(1, 20, 3, 120, 300, T_turret1, vectorTurret1);
	turret2 = new Turret(2, 10, 1, 30, 200, T_turret2, vectorTurret2);
	turret3 = new Turret(3, 50, 1, 30, 100, T_turret3, vectorTurret3);

	T_monster1.setSmooth(true);
	T_monster2.setSmooth(true);
	T_missile1.setSmooth(true);
	T_missile2.setSmooth(true);
	T_missile3.setSmooth(true);

	T_cursor1.setSmooth(true);
	T_cursor2.setSmooth(true);
	T_cursor3.setSmooth(true);
	T_cursor4.setSmooth(true);
	cursor.setTexture(T_cursor4);
	cursor.setTexture(T_cursor1);

	texts[0].setPosition(552, 627);
	texts[1].setPosition(567, 649);
	texts[2].setPosition(580, 671);
	texts[3].setPosition(vectorTurret1.x - 33, vectorTurret1.y - 40);
	texts[4].setPosition(vectorTurret2.x - 33, vectorTurret2.y - 40);
	texts[5].setPosition(vectorTurret3.x - 33, vectorTurret3.y - 40);
	texts[3].setString(to_string((*turret1).price) + "$");
	texts[4].setString(to_string((*turret2).price) + "$");
	texts[5].setString(to_string((*turret3).price) + "$");
	texts[6].setPosition(756, 628);
	texts[7].setPosition(764, 650);
	texts[8].setPosition(752, 672);
	for (int i = 0; i < 9; i++)
	{
		texts[i].setFont(font);
		texts[i].setCharacterSize(18);
		texts[i].setOrigin(0, texts[i].getGlobalBounds().height / 2);
	}
	updateInfo();

	/*text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(Color(255, 255, 255));
	text.setPosition(20, 20);*/
}

void Game::events()
{
	sf::Event e;
	while (window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
		{
			cleaner();
			window.close();
			exit(0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Space))					//usunac
		{
			Sleep(1000);
		}
		if (e.type == Event::KeyPressed && e.key.code == Keyboard::W)		//usunac
		{
			Sleep(100);
		}
		if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left)
		{
			leftButtonPressed();
		}
		if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Right)
		{
			cursor.setTexture(T_cursor1);
			cursor.setOrigin(0, 0);
			ifMovingTurret = 0;
			(*turret1).picture.setPosition(vectorTurret1);
			(*turret2).picture.setPosition(vectorTurret2);
			(*turret3).picture.setPosition(vectorTurret3);
			circle.setPosition(0, 0);
			circle.setRadius(0);
			updateInfo();
		}
	}
}

void Game::leftButtonPressed()
{
	Vector2i position = Mouse::getPosition(window);
	if (position.y >= 625 && position.x >= 921)			//tu wstawic ulepszanie wiezyczek
	{
		timeToNextRound = 0;
		return;
	}
	else if (ifMovingTurret)
	{
		movingTurret();
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
	
	turretClicked();
}

void Game::movingTurret()
{
	bool tmp = 0;
	switch (ifMovingTurret)
	{
	case 1:
		if (cash >= (*turret1).getPrice() && checkPlace((*turret1).picture.getPosition(), (*turret1).picture.getGlobalBounds().width, (*turret1).picture.getGlobalBounds().height))
		{
			tmp = 1;
			cash -= (*turret1).getPrice();
			turrets.push_back(*turret1);
			(*turret1).picture.setPosition(vectorTurret1);
			updateInfo();
		}
		break;
	case 2:
		if (cash >= (*turret2).getPrice() && checkPlace((*turret2).picture.getPosition(), (*turret2).picture.getGlobalBounds().width, (*turret2).picture.getGlobalBounds().height))
		{
			tmp = 1;
			cash -= (*turret2).getPrice();
			turrets.push_back(*turret2);
			(*turret2).picture.setPosition(vectorTurret2);
			updateInfo();
		}
		break;
	case 3:
		if (cash >= (*turret3).getPrice() && checkPlace((*turret3).picture.getPosition(), (*turret3).picture.getGlobalBounds().width, (*turret3).picture.getGlobalBounds().height))
		{
			tmp = 1;
			cash -= (*turret3).getPrice();
			turrets.push_back(*turret3);
			(*turret3).picture.setPosition(vectorTurret3);
			updateInfo();
		}
		break;
	}
	if (!tmp)
	{
		return;
	}
	cursor.setTexture(T_cursor1);
	cursor.setOrigin(0, 0);
	ifMovingTurret = 0;
	circle.setPosition(0, 0);
	circle.setRadius(0);
	clicked = -1;
}

bool Game::notMovingTurret()
{
	if ((*turret1).picture.getGlobalBounds().contains((Vector2f)Mouse::getPosition(window)))
	{
		cursor.setTexture(T_cursor4);
		cursor.setOrigin(cursor.getGlobalBounds().width / 2, cursor.getGlobalBounds().height / 2);
		ifMovingTurret = 1;
		updateInfo((*turret1));
		return true;
	}
	else if ((*turret2).picture.getGlobalBounds().contains((Vector2f)Mouse::getPosition(window)))
	{
		cursor.setTexture(T_cursor4);
		cursor.setOrigin(cursor.getGlobalBounds().width / 2, cursor.getGlobalBounds().height / 2);
		ifMovingTurret = 2;
		updateInfo((*turret2));
		return true;
	}
	else if ((*turret3).picture.getGlobalBounds().contains((Vector2f)Mouse::getPosition(window)))
	{
		cursor.setTexture(T_cursor4);
		cursor.setOrigin(cursor.getGlobalBounds().width / 2, cursor.getGlobalBounds().height / 2);
		ifMovingTurret = 3;
		updateInfo((*turret3));
		return true;
	}
	return false;
}

bool Game::turretClicked()
{
	if (Mouse::getPosition(window).y <= 624)
	{
		for (unsigned i = 0; i < turrets.size(); i++)
		{
			if (turrets[i].picture.getGlobalBounds().contains((Vector2f)Mouse::getPosition(window)))
			{
				clicked = i;
				updateCircle((turrets.begin() + clicked)->picture.getPosition(), (turrets.begin() + clicked)->range);
				updateInfo(*(turrets.begin() + clicked));
				return true;
			}
		}
		clicked = -1;
		updateCircle(Vector2f(0, 0), 0);
		updateInfo();
		return false;
	}
}

void Game::upgradeTurrets()
{
	if (texts[0].getGlobalBounds().contains((Vector2f)Mouse::getPosition(window)))
	{
		turrets[clicked].upgrade(0, cash);
	}
	else if (texts[1].getGlobalBounds().contains((Vector2f)Mouse::getPosition(window)))
	{
		turrets[clicked].upgrade(1, cash);
	}
	else if (texts[2].getGlobalBounds().contains((Vector2f)Mouse::getPosition(window)))
	{
		turrets[clicked].upgrade(2, cash);
	}
}

void Game::updateCircle(const Vector2f & position, const int & range)
{
	circle.setPosition(position);
	circle.setRadius(range);
	circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
}

void Game::updateInfo()
{
	texts[0].setString("Damage");
	texts[1].setString("Range");
	texts[2].setString("Rate");
	texts[0].setFillColor(Color(130, 130, 130));
	texts[1].setFillColor(Color(130, 130, 130));
	texts[2].setFillColor(Color(130, 130, 130));
}

void Game::updateInfo(const Turret & turret)
{
	texts[0].setString("Damage  " + to_string(turret.damage));
	texts[1].setString("Range  " + to_string(turret.range));
	texts[2].setString("Rate  " + to_string(turret.rate));
	texts[0].setFillColor(Color::White);
	texts[1].setFillColor(Color::White);
	texts[2].setFillColor(Color::White);
}

void Game::display()
{
	window.clear(Color(255, 0, 0));
	window.draw(map);
	window.draw(bar);
	window.draw(arrow);
	texts[6].setString("Cash  " + to_string(cash) + "$");
	texts[7].setString("Kills  " + to_string(kills));
	texts[8].setString("Wave  " + to_string(level));
	for (int i = 0; i < 9; i++)
	{
		window.draw(texts[i]);
	}
	window.draw(circle);


	for (unsigned i = 0; i < lines.size(); i++)
	{
		window.draw(lines[i]);
	}
	for (unsigned i = 0; i < monsters.size(); i++)
	{
		monsters[i].display(window);
	}
	for (unsigned i = 0; i < turrets.size(); i++)
	{
		window.draw(turrets[i].picture);
	}
	for (auto r : rockets)
	{
		(*r).display(window);
	}

	switch (ifMovingTurret)
	{
	case 1:
		(*turret1).picture.setPosition((Vector2f)Mouse::getPosition(window));
		updateCircle((Vector2f)Mouse::getPosition(window), (*turret1).range);
		break;
	case 2:
		(*turret2).picture.setPosition((Vector2f)Mouse::getPosition(window));
		circle.setPosition((Vector2f)Mouse::getPosition(window));
		circle.setRadius((*turret2).range);
		circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
		break;
	case 3:
		(*turret3).picture.setPosition((Vector2f)Mouse::getPosition(window));
		circle.setPosition((Vector2f)Mouse::getPosition(window));
		circle.setRadius((*turret3).range);
		circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
		break;
	}
	window.draw((*turret1).picture);
	window.draw((*turret2).picture);
	window.draw((*turret3).picture);
	cursor.setPosition(Vector2f(Mouse::getPosition(window)));
	window.draw(cursor);

	window.display();
	timeToNextRound--;
}

void Game::updateClock()
{
	arrow.setRotation(timeToNextRound / 3.33);
}

void Game::move_monsters()
{
	for (unsigned i = 0; i < monsters.size(); i++)
	{
		if (monsters[i].move(map1))
		{
			lines.push_back(Sprite(T_line));
			lines.back().setOrigin(lines.back().getGlobalBounds().width / 2, lines.back().getGlobalBounds().height / 2);
			lines.back().setPosition(343 + 20 * lines.size(), 272);
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
		for (int i = 0; i < 10; i++)
		{
			if(level % 2 == 0)
				monsters.push_back(Monster(level, font, T_monster2, Vector2f(920, -60 * i)));
			else
				monsters.push_back(Monster(level, font, T_monster1, Vector2f(920, -60 * i)));
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

void Game::move_rockets()
{
	for (int i = 0; i < rockets.size(); i++)
	{
		if ((*rockets[i]).specialAbilities(monsters, cash, kills))
		{
			delete rockets[i];
			rockets.erase(rockets.begin() + i);
			i--;
		}
	}
}

bool Game::checkPixel(int x, int y)
{
	if (((int)I_map.getPixel(x, y).r >= 143 && (int)I_map.getPixel(x, y).r <= 149 && (int)I_map.getPixel(x, y).g >= 205 &&
		(int)I_map.getPixel(x, y).g <= 211 && (int)I_map.getPixel(x, y).b >= 77 && (int)I_map.getPixel(x, y).b <= 83) ||
		((int)I_map.getPixel(x, y).r > 252 && (int)I_map.getPixel(x, y).g < 5 && (int)I_map.getPixel(x, y).b < 5))
	{
		return false;
	}
	return true;
}

bool Game::checkPlace(Vector2f position, int w, int h)
{
	int i;
	if (position.y + h / 2 + 3 <= 624)
	{
		for ((position.y - h / 2 - 3 >= 0) ? (i = position.y - h / 2 - 3) : i = 0; i < position.y + h / 2 + 3 && i < height; i++)
		{
			if (!checkPixel(position.x, i) || !checkPixel(position.x + w/2 - 1, i))
			{
				return false;
			}
		}
		for ((position.x - w / 2 - 3 >= 0) ? (i = position.x - w / 2 - 3) : (i = 0); i < position.x + w / 2 + 3 && i < width; i++)
		{
			if (!checkPixel(i, position.y) || !checkPixel(i, position.y + h/2 - 1))
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
		if (sqrt(pow(t.picture.getPosition().x - position.x, 2) + pow(t.picture.getPosition().y - position.y, 2)) <= 53)
		{
			return false;
		}
	}
	return true;
}

void Game::shoot()
{
	int tmp;
	for (auto & t : turrets)
	{
		tmp = t.shoot(monsters);
		if (tmp >= 0 && tmp < monsters.size())
		{
			switch (t.id)
			{
			case 1:
				rockets.push_back(new Rocket1(2, t.damage, t.picture.getRotation(), 3, tmp, T_missile1, t.picture.getPosition()));
				break;
			case 2:
				rockets.push_back(new Rocket2(20, t.damage, t.picture.getRotation(), tmp, T_missile2, t.picture.getPosition()));
				break;
			case 3:
				rockets.push_back(new Rocket3(1, t.damage, t.picture.getRotation(), 10, tmp, T_missile3, t.picture.getPosition()));
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
		T_screenShot.update(window);
		screenShot.setTexture(T_screenShot);
		cleaner();
		exit(0);
	}
}

void Game::cleaner()
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

}
