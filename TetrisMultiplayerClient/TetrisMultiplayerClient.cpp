// TetrisMultiplayerClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TetrominoI.h"
#include "TetrominoFactory.h"
#include "SingleGame.h"
#include <string>
#include "SFML\Network.hpp"

using namespace std;

int main()
{
	string serverIp, nick;
	int serverPort;

	cout << "TETRIS MULTIPLAYER SERVER" << endl << endl;
	cout << "Autorzy: " << endl;
	cout << "Marcin Muskala" << endl;
	cout << "Marek Nawrot" << endl;
	cout << "Michal Sliwa" << endl;
	cout << "Rafal Zieba" << endl << endl;

	cout << "Podaj numer ip serwera: ";
	cin >> serverIp;
	cout << "Podaj numer portu dla serwera: ";
	cin >> serverPort;
	cout << "Podaj swoj nick: ";
	cin >> nick;

	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(serverIp, serverPort);
	if (status != sf::Socket::Done)
	{
		cout << "Podczas laczenia z serwerem wystapil blad.";
	}

	sf::Packet packet;
	string cmd = "connect";
	packet << cmd << nick;
	socket.send(packet);

	/*
		Player player("Player", 1);
	ParentGameEngine *singleGame = new SingleGame(player);

	singleGame->startThread();
	while (true)
	{
		this_thread::sleep_for(chrono::milliseconds(100000));
	}

	sf::RenderWindow window(sf::VideoMode(200, 400), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	sf::RectangleShape rectangle;
	sf::Vector2i  vector = sf::Vector2i(100,40);
	sf::Vector2i  vector2 = sf::Vector2i(100, 380);

	TetrominoFactory tetrominoFactory = TetrominoFactory();
	Tetromino tetromino = tetrominoFactory.getRandomTetromino(vector);
	Tetromino *tet = &tetromino;
	Tetromino tetromino2 = tetrominoFactory.getRandomTetromino(vector2);
	Tetromino *tet2 = &tetromino2;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Right)
				{
					std::cout << "right";
					if (!tet->checkColision(*tet2, RIGHT, 200))
					{
						tet->moveRight();
					}
				}
				else if (event.key.code == sf::Keyboard::Left)
				{
					std::cout << "left";
					if (!tet->checkColision(*tet2, LEFT, 200))
					{
						tet->moveLeft();
					}
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					std::cout << "down";
					if (!tet->checkColision(*tet2, DOWN, 200))
					{
						tet->moveDown();
					}
				}
				else if (event.key.code == sf::Keyboard::Up)
				{
					std::cout << "rotate";
					if (!tet->checkColision(*tet2, ROTATE, 200))
					{
						tet->rotate();
					}
				}
				else if (event.key.code == sf::Keyboard::R)
				{
					std::cout << "random";
					tetromino = tetrominoFactory.getRandomTetromino(vector);
				}
				else if (event.key.code == sf::Keyboard::Space)
				{
					std::cout << "drop";
					int dropAmount = tet->getDropCount(*tet2, 200);
					tet->drop(dropAmount);
				}
				else if (event.key.code == sf::Keyboard::C)
				{
					std::cout << "clear line 2";
					tet->clearLine(2);
				}
				else
				{
					std::cout << event.key.code;
				}
			}
		}
		window.clear();
		for (sf::RectangleShape rectangle : tet->getDrawableItems())
		{
			window.draw(rectangle);
		}
		for (sf::RectangleShape rectangle : tet2->getDrawableItems())
		{
			window.draw(rectangle);
		}
		window.display();
	}*/

	return 0;
}

