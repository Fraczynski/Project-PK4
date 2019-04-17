#include "GUI.h"
#include <string.h>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void GUI::loadGraphics()
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
		if (!I_map.loadFromFile("map1.png") || !T_map.loadFromFile("map1.png") || !T_bar.loadFromFile("bar.png") || !T_turret1.loadFromFile("turret1.png") || !T_turret2.loadFromFile("turret2.png") ||
			!T_turret3.loadFromFile("turret3.png") || !T_monster1.loadFromFile("monster1.png") || !T_monster2.loadFromFile("monster2.png") ||
			!T_cursor1.loadFromFile("cursor1.png") || !T_cursor2.loadFromFile("cursor2.png") ||
			!T_cursor3.loadFromFile("cursor3.png") || !T_cursor4.loadFromFile("cursor4.png") || !T_missile1.loadFromFile("missile1.png") || !T_missile2.loadFromFile("missile2.png") ||
			!T_missile3.loadFromFile("missile3.png") || !T_arrow.loadFromFile("arrow.png") || !font.loadFromFile("calibri.ttf") || !T_line.loadFromFile("line.png") ||
			!T_gameOver.loadFromFile("end.png"))
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

void GUI::display()
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

void GUI::end()
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
