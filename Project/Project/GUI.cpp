#include <string.h>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "GUI.h"
#include "Icon.h"

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
		if (!T_background.loadFromFile("background.png") || !I_map1.loadFromFile("map1.png") || !T_map1.loadFromFile("map1.png") || !T_bar.loadFromFile("bar.png") ||
			!T_turret1.loadFromFile("turret1.png") || !T_turret2.loadFromFile("turret2.png") || !T_turret3.loadFromFile("turret3.png") || !T_monster1.loadFromFile("monster1.png") ||
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

	T_monster1.setSmooth(true);
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

void GUI::display(vector<Monster> & monsters, vector<Turret> & turrets, vector<Rocket *> & rockets, vector<Sprite> & lines, int & clicked, int & cash, int & kills, int & level, int & timeToNextRound)
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

void GUI::pauseMenu(const Sprite & cursorTmp)
{
	window.draw(screenShot);
	window.draw(buttonResume);
	window.draw(buttonRestart);
	window.draw(buttonSave);
	window.draw(buttonLoad);
	window.draw(buttonExit);
	window.draw(cursorTmp);
	window.display();
}

bool GUI::endAnimation(vector<Sprite> & lines)
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

