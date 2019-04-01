
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
		monsters.push_back(Monster(1, font, T_monster1, Vector2f(709, 200 + i * 10)));				//usunac po testach

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
	if (!I_map.loadFromFile("map1.png") || !T_map.loadFromFile("map1.png") || !T_bar.loadFromFile("bar.png") || !T_turret1.loadFromFile("turret1.png") || !T_turret2.loadFromFile("turret2.png") ||
		!T_turret3.loadFromFile("turret3.png") || !T_monster1.loadFromFile("monster1.png") || !T_cursor1.loadFromFile("cursor1.png") || !T_cursor2.loadFromFile("cursor2.png") || 
		!T_cursor3.loadFromFile("cursor3.png") || !T_cursor4.loadFromFile("cursor4.png") || !T_missile1.loadFromFile("missile1.png") || !T_arrow.loadFromFile("arrow.png") || 
		!font.loadFromFile("calibri.ttf") || !T_line.loadFromFile("line.png") || !T_gameOver.loadFromFile("end.png"))
	{
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
	turret1.setTexture(T_turret1);
	turret1.setOrigin(turret1.getGlobalBounds().width / 2, turret1.getGlobalBounds().height / 2);
	turret1.setPosition(vectorTurret1);
	turret2.setTexture(T_turret2);
	turret2.setOrigin(turret2.getGlobalBounds().width / 2, turret2.getGlobalBounds().height / 2);
	turret2.setPosition(vectorTurret2);
	turret3.setTexture(T_turret3);
	turret3.setOrigin(turret3.getGlobalBounds().width / 2, turret3.getGlobalBounds().height / 2);
	turret3.setPosition(vectorTurret3);

	T_monster1.setSmooth(true);
	T_missile1.setSmooth(true);

	T_cursor1.setSmooth(true);
	T_cursor2.setSmooth(true);
	T_cursor3.setSmooth(true);
	T_cursor4.setSmooth(true);
	cursor.setTexture(T_cursor4);
	cursor.setTexture(T_cursor1);

	T_cash.setFont(font);
	T_cash.setCharacterSize(20);
	T_cash.setFillColor(Color(255, 255, 255));
	T_cash.setPosition(804, 628);
	T_cash.setOrigin(0, T_cash.getGlobalBounds().height / 2);
	T_kills.setFont(font);
	T_kills.setCharacterSize(20);
	T_kills.setFillColor(Color(255, 255, 255));
	T_kills.setPosition(804, 650);
	T_kills.setOrigin(0, T_kills.getGlobalBounds().height / 2);
	T_waves.setFont(font);
	T_waves.setCharacterSize(20);
	T_waves.setFillColor(Color(255, 255, 255));
	T_waves.setPosition(804, 672);
	T_waves.setOrigin(0, T_waves.getGlobalBounds().height / 2);

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
			window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			Sleep(1000);
		}
		if (e.type == Event::KeyPressed && e.key.code == Keyboard::W)
		{
			Sleep(100);
		}
		if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left)
		{
			leftButtonPressed();
		}
	}
}

void Game::leftButtonPressed()
{
	//klikniecie prawym powoduje przerwanie przenoszenia wiezyczki
	Vector2i position = Mouse::getPosition(window);
	if (position.y >= 625 && position.x >= 921)
	{
		timeToNextRound = 0;
	}
	else if (!ifMovingTurret)
	{
		notMovingTurret();
	}
	else if (ifMovingTurret)
	{
		movingTurret();
	}
}

void Game::movingTurret()
{
	switch (ifMovingTurret)
	{
	case 1:
		if (checkPlace(turret1.getPosition(), turret1.getGlobalBounds().width, turret1.getGlobalBounds().height))
		{
			cursor.setTexture(T_cursor1);
			cursor.setOrigin(0, 0);
			ifMovingTurret = 0;
			turrets.push_back(Turret(3, 120, 300, T_turret1, turret1.getPosition()));
			turret1.setPosition(vectorTurret1);
			circle.setPosition(0, 0);
			circle.setRadius(0);
		}
		break;
	case 2:
		if (checkPlace(turret2.getPosition(), turret2.getGlobalBounds().width, turret3.getGlobalBounds().height))
		{
			cursor.setTexture(T_cursor1);
			cursor.setOrigin(0, 0);
			ifMovingTurret = 0;
			turrets.push_back(Turret(1, 30, 200, T_turret2, turret2.getPosition()));
			turret2.setPosition(vectorTurret2);
			circle.setPosition(0, 0);
			circle.setRadius(0);
		}
		break;
	case 3:
		if (checkPlace(turret3.getPosition(), turret3.getGlobalBounds().width, turret3.getGlobalBounds().height))
		{
			cursor.setTexture(T_cursor1);
			cursor.setOrigin(0, 0);
			ifMovingTurret = 0;
			turrets.push_back(Turret(1, 0, 100, T_turret3, turret3.getPosition()));
			turret3.setPosition(vectorTurret3);
			circle.setPosition(0, 0);
			circle.setRadius(0);
		}
		break;
	}
}

void Game::notMovingTurret()
{
	if (turret1.getGlobalBounds().contains((Vector2f)Mouse::getPosition(window)))
	{
		cursor.setTexture(T_cursor4);
		cursor.setOrigin(cursor.getGlobalBounds().width / 2, cursor.getGlobalBounds().height / 2);
		ifMovingTurret = 1;
	}
	else if (turret2.getGlobalBounds().contains((Vector2f)Mouse::getPosition(window)))
	{
		cursor.setTexture(T_cursor4);
		cursor.setOrigin(cursor.getGlobalBounds().width / 2, cursor.getGlobalBounds().height / 2);
		ifMovingTurret = 2;
	}
	else if (turret3.getGlobalBounds().contains((Vector2f)Mouse::getPosition(window)))
	{
		cursor.setTexture(T_cursor4);
		cursor.setOrigin(cursor.getGlobalBounds().width / 2, cursor.getGlobalBounds().height / 2);
		ifMovingTurret = 3;
	}
}

void Game::display()
{
	window.clear(Color(255, 0, 0));
	window.draw(map);
	window.draw(bar);
	window.draw(arrow);
	T_cash.setString(to_string(cash));
	window.draw(T_cash);
	T_kills.setString(to_string(kills));
	window.draw(T_kills);
	T_waves.setString(to_string(level));
	window.draw(T_waves);

	for (auto r : lines)
	{
		window.draw(r);
	}
	for (auto m : monsters)
	{
		m.display(window);
	}
	for (auto t : turrets)
	{
		window.draw(t.picture);
	}
	for (auto r : rockets)
	{
		window.draw(r.picture);
	}

	switch (ifMovingTurret)
	{
	case 1:
		turret1.setPosition((Vector2f)Mouse::getPosition(window));
		circle.setPosition((Vector2f)Mouse::getPosition(window));
		circle.setRadius(200);															//poprawic wielkosc kola zasiegu
		circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
		break;
	case 2:
		turret2.setPosition((Vector2f)Mouse::getPosition(window));
		circle.setPosition((Vector2f)Mouse::getPosition(window));
		circle.setRadius(200);
		circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
		break;
	case 3:
		turret3.setPosition((Vector2f)Mouse::getPosition(window));
		circle.setPosition((Vector2f)Mouse::getPosition(window));
		circle.setRadius(200);
		circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
		break;
	}
	window.draw(circle);
	window.draw(turret1);
	window.draw(turret2);
	window.draw(turret3);
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
		switch (monsters[i].move(map1))
		{
		case 2:
			lines.push_back(Sprite(T_line));
			lines.back().setOrigin(lines.back().getGlobalBounds().width / 2, lines.back().getGlobalBounds().height / 2);
			lines.back().setPosition(343 + 20 * lines.size(), 272);
		case 1:
			monsters.erase(monsters.begin() + i);
			i--;
			break;
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
			monsters.push_back(Monster(level, font, T_monster1, Vector2f(920, - 60 * i)));
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
	if (monsters.empty() == 0)
	{
		for (int i = 0; i < rockets.size(); i++)
		{
			if (rockets[i].move(monsters, cash, kills))
			{
				rockets.erase(rockets.begin() + i);
				i--;
			}
		}
	}
}

bool Game::checkPlace(Vector2f position, int w, int h)
{
	//poprawic zeby sprawdzal tylko krawedzie i polozenie innych wiezyczek
	int i, j;
	for ((position.y - h / 2 - 3 >= 0) ? (j = position.y - h / 2 - 3) : j = 0; j < position.y + h / 2 + 3 && j < height; j++)
	{
		for ( (position.x - w / 2 - 3 >= 0) ? (i = position.x - w / 2 - 3) : (i = 0); i < position.x + w / 2 + 3 && j < width; i++)
		{
			if (position.y + h / 2 + 3 >= 625 || ((int)I_map.getPixel(i, j).r == 146 && (int)I_map.getPixel(i, j).g == 209 && (int)I_map.getPixel(i, j).b == 79) ||
				((int)I_map.getPixel(i, j).r == 254 && (int)I_map.getPixel(i, j).g < 5 && (int)I_map.getPixel(i, j).b < 5))
			{
				return false;
			}
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
			rockets.push_back(Rocket(2, t.damage, t.picture.getRotation(), 3, tmp, T_missile1, t.picture.getPosition()));
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
		exit(0);
	}
}
