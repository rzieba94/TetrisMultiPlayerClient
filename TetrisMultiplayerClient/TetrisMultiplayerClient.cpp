// TetrisMultiplayerClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TetrominoI.h"
#include "TetrominoFactory.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 400), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	sf::RectangleShape rectangle;
	sf::Vector2i  vector = sf::Vector2i(100,40);

	TetrominoFactory tetrominoFactory = TetrominoFactory();
	Tetromino tetromino = tetrominoFactory.getRandomTetromino(vector);
	TetrisShape *tet = &tetromino;

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
					tet->moveRight();
				}
				else if (event.key.code == sf::Keyboard::Left)
				{
					std::cout << "left";
					tet->moveLeft();
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					std::cout << "down";
					tet->moveDown();
				}
				else if (event.key.code == sf::Keyboard::Up)
				{
					std::cout << "rotate";
					tet->rotate();
				}
				else if (event.key.code == sf::Keyboard::R)
				{
					std::cout << "random";
					tetromino = tetrominoFactory.getRandomTetromino(vector);
				}
				else if (event.key.code == sf::Keyboard::Space)
				{
					std::cout << "drop";
					tet->drop(5);
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
		window.display();
	}

	return 0;
}

