// TetrisMultiplayerClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TetrominoI.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	sf::RectangleShape rectangle;
	sf::Vector2i * vector = new sf::Vector2i(1,2);
	sf::Color * color =  new sf::Color(1,1,1,255);
	TetrominoI tet(vector, color);
	tet.moveLeft();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::A)
				{
					std::cout << "the escape a was pressed" << std::endl;
					std::cout << "control:" << event.key.control << std::endl;
					std::cout << "alt:" << event.key.alt << std::endl;
					std::cout << "shift:" << event.key.shift << std::endl;
					std::cout << "system:" << event.key.system << std::endl;
				}
			}
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}

