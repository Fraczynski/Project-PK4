#include "GUI.h"
#include <chrono>
#include <thread>

using namespace std;

void GUI::loadGraphics()
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
			!T_line.loadFromFile("line.png") || !T_gameOver.loadFromFile("end.png") || !T_button.loadFromFile("button.png") || !T_buttonSmall.loadFromFile("buttonSmall.png") ||
			!T_background.loadFromFile("background.png") ||
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
		this_thread::sleep_for(chrono::seconds(3));
		window.close();
		return;
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
	T_buttonSmall.setSmooth(true);
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
	buttonResume.reset(new Button(T_button, fontTimesNewRoman, Vector2f(float(width / 2), float(2 * height / 8)), "RESUME"));
	buttonRestart.reset(new Button(T_button, fontTimesNewRoman, Vector2f(float(width / 2), float(3 * height / 8)), "RESTART"));
	buttonSave.reset(new Button(T_button, fontTimesNewRoman, Vector2f(float(width / 2), float(4 * height / 8)), "SAVE"));
	buttonLoad.reset(new Button(T_button, fontTimesNewRoman, Vector2f(float(width / 2), float(5 * height / 8)), "LOAD"));
	buttonExit.reset(new Button(T_button, fontTimesNewRoman, Vector2f(float(width / 2), float(6 * height / 8)), "EXIT"));

	//ustawianie przyciskow ulepszen
	buttonUpgradingDamage.reset(new Button(T_buttonSmall, fontTimesNewRoman, Vector2f(677, 640), ""));
	buttonUpgradingRange.reset(new Button(T_buttonSmall, fontTimesNewRoman, Vector2f(677, 662), ""));
	buttonUpgradingRate.reset(new Button(T_buttonSmall, fontTimesNewRoman, Vector2f(677, 684), ""));

	//ustawienie kursora
	cursor.setTexture(T_cursor2);
	cursor.setTexture(T_cursor1);
}

void GUI::display(vector<Turret> & turrets, vector<Monster> & monsters, vector<unique_ptr<Rocket>> & rockets, const int & clicked, const int & cash, const int & kills,
					const int & level, int & timeToNextRound, Turret * turret1, Turret * turret2, Turret * turret3)
{
	if (!window.isOpen())
		return;

	updateClock(timeToNextRound);
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
	buttonUpgradingDamage->display(window);
	buttonUpgradingRange->display(window);
	buttonUpgradingRate->display(window);
	texts->display(cash, kills, level, window);

	turret1->display(window);
	turret2->display(window);
	turret3->display(window);
	cursor.setPosition(Vector2f(Mouse::getPosition(window)));
	window.draw(cursor);

	window.display();
	timeToNextRound--;
}

Vector2i GUI::getMousePosition()
{
	return Vector2i(Mouse::getPosition(window));
}

void GUI::changeCursor(int cursorNumber)
{
	if(cursorNumber == 2)
		cursor.setTexture(T_cursor2);
	else
		cursor.setTexture(T_cursor1);
	cursor.setOrigin(cursor.getGlobalBounds().width / 2, cursor.getGlobalBounds().height / 2);
}

void GUI::updateInfo(Turret & turret)
{
	texts->updateInfo(turret);
}

void GUI::updateInfo()
{
	texts->updateInfo();
}

void GUI::setTexts(Turret * turret1, Turret * turret2, Turret * turret3)
{
	//ustawienie tekstow wyswietlanych na pasku gry
	texts.reset(new Texts(fontCalibri, Vector2f(vectorTurret1.x, vectorTurret1.y - 5), Vector2f(vectorTurret2.x, vectorTurret2.y - 5), Vector2f(vectorTurret3.x, vectorTurret3.y - 5), turret1, turret2, turret3));
	texts->updateInfo();
}

void GUI::setMenuGraphics()
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
}

void GUI::resetMenuGraphics()
{
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

void GUI::displayMenu()
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

void GUI::resetTurrets()
{
	cursor.setTexture(T_cursor1);
	cursor.setOrigin(0, 0);
	circle.setPosition(0, 0);
	circle.setRadius(0);
	texts->updateInfo();
}

bool GUI::pollEvent(Event & e)
{
	return window.pollEvent(e);
}

bool GUI::isButtonResumeClicked()
{
	return buttonResume->contains((Vector2f)Mouse::getPosition(window));
}

bool GUI::isButtonRestartClicked()
{
	return buttonRestart->contains((Vector2f)Mouse::getPosition(window));
}

bool GUI::isButtonSaveClicked()
{
	return buttonSave->contains((Vector2f)Mouse::getPosition(window));
}

bool GUI::isButtonLoadClicked()
{
	return buttonLoad->contains((Vector2f)Mouse::getPosition(window));
}

bool GUI::isButtonExitClicked()
{
	return buttonExit->contains((Vector2f)Mouse::getPosition(window));
}

bool GUI::isButtonMapClicked()
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
	return false;
}

void GUI::linesClear()
{
	lines.clear();
}

int GUI::selectedMap()
{
	if (map == &map1)
		return 1;
	else if (map == &map2)
		return 2;
}

int GUI::getLinesNumber()
{
	return lines.size();
}

void GUI::takeScreenshot(vector<Turret> & turrets, vector<Monster> & monsters, vector<unique_ptr<Rocket>> & rockets, const int & clicked, const int & cash, const int & kills,
	const int & level, int & timeToNextRound, Turret * turret1, Turret * turret2, Turret * turret3)
{
	mousePosition = getMousePosition();
	Mouse::setPosition(Vector2i(0, -32), window);
	display(turrets, monsters, rockets, clicked, cash, kills, level, timeToNextRound, turret1, turret2, turret3);
	display(turrets, monsters, rockets, clicked, cash, kills, level, timeToNextRound, turret1, turret2, turret3);
	display(turrets, monsters, rockets, clicked, cash, kills, level, timeToNextRound, turret1, turret2, turret3);
	T_screenShot.update(window);
	screenShot.setTexture(T_screenShot);
	screenShot.setColor(Color(110, 110, 110));
	Mouse::setPosition(mousePosition, window);
	cursorPtr = cursor.getTexture();
	cursor.setTexture(T_cursor1);
}

void GUI::restoreCursor()
{
	cursor.setTexture(*cursorPtr);
}

int GUI::upgradingTextClicked()
{
	return texts->upgradingTextClicked(window);
}

int GUI::getHeight()
{
	return height;
}

int GUI::getWidth()
{
	return width;
}

void GUI::pauseDisplay()
{
	cursor.setPosition(Vector2f(Mouse::getPosition(window)));
	window.draw(screenShot);
	buttonResume->display(window);
	buttonRestart->display(window);
	buttonSave->display(window);
	buttonLoad->display(window);
	buttonExit->display(window);
	window.draw(cursor);
	window.display();
}

void GUI::endAnimation()
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
			this_thread::sleep_for(chrono::milliseconds(15));
		}
		this_thread::sleep_for(chrono::seconds(3));
		window.close();
	}
}

void GUI::checkCorners(list<Map> & mapCorners)
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

void GUI::updateClock(const int & timeToNextRound)
{
	arrow.setRotation(float(timeToNextRound / 3.33));
}

bool GUI::isOpen()
{
	return window.isOpen();
}

void GUI::close()
{
	window.close();
}

bool GUI::checkPixel(const int & x, const int & y)
{
	if (((int)I_map.getPixel(x, y).r >= 143 && (int)I_map.getPixel(x, y).r <= 149 && (int)I_map.getPixel(x, y).g >= 205 &&
		(int)I_map.getPixel(x, y).g <= 211 && (int)I_map.getPixel(x, y).b >= 77 && (int)I_map.getPixel(x, y).b <= 83) ||
		((int)I_map.getPixel(x, y).r > 252 && (int)I_map.getPixel(x, y).g < 5 && (int)I_map.getPixel(x, y).b < 5))
	{
		return false;
	}
	return true;
}

void GUI::addLines()
{
	lines.push_back(Sprite(T_line));
	lines.back().setOrigin(lines.back().getGlobalBounds().width / 2, lines.back().getGlobalBounds().height / 2);
	lines.back().setPosition(endLinesMap->x + 20 * (float)lines.size(), endLinesMap->y);
}

void GUI::updateCircle(const Vector2i & position, const int & range)
{
	circle.setPosition(Vector2f(position));
	circle.setRadius((float)range);
	circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
}
