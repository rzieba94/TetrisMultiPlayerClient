#include "stdafx.h"
#include "SingleGame.h"
#include <iostream>
#include <thread>

using namespace std;

SingleGame::SingleGame(Player player) : player(player)
{
	this->window = new sf::RenderWindow(sf::VideoMode(200, 400), "Tetris Multiplayer");
}


SingleGame::~SingleGame()
{
}

void SingleGame::run()
{
	placeNewTetromino();
	while (window->isOpen())
	{
		checkPlayersMove(*window);
		notActiveTetrominos.clearLine(getLineToClear());
		cout << "tutaj1";
		if (checkForInactiveBlock())
		{
			cout << "tutaj3";
			if (!placeNewTetromino())
			{
				return;
			}
		}
		cout << "tutaj2";
		displayInWindow(*window);
		checkFrameTime();
	}
}

void SingleGame::displayInWindow(sf::RenderWindow & window)
{
	window.clear();
	shared_ptr<Tetromino> activeTetromino = player.getActiveTetromino();
	for (sf::RectangleShape rectangle : activeTetromino->getDrawableItems())
	{
		window.draw(rectangle);
	}
	for (sf::RectangleShape rectangle : notActiveTetrominos.getDrawableItems())
	{
		window.draw(rectangle);
	}
	window.display();
}

void SingleGame::checkPlayersMove(sf::RenderWindow & window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Right)
			{
				if (!player.getActiveTetromino()->checkColision(notActiveTetrominos, RIGHT, 200))
				{
					player.getActiveTetromino()->moveRight();
				}
			}
			else if (event.key.code == sf::Keyboard::Left)
			{
				if (!player.getActiveTetromino()->checkColision(notActiveTetrominos, LEFT, 200))
				{
					player.getActiveTetromino()->moveLeft();
				}
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				if (!player.getActiveTetromino()->checkColision(notActiveTetrominos, DOWN, 200))
				{
					player.getActiveTetromino()->moveDown();
				}
			}
			else if (event.key.code == sf::Keyboard::Up)
			{
				if (!player.getActiveTetromino()->checkColision(notActiveTetrominos, ROTATE, 200))
				{
					player.getActiveTetromino()->rotate();
				}
			}
			else if (event.key.code == sf::Keyboard::Space)
			{
				int dropAmount = player.getActiveTetromino()->getDropCount(notActiveTetrominos, 200);
				player.getActiveTetromino()->drop(dropAmount);
			}
		}
	}
}

bool SingleGame::placeNewTetromino()
{
	shared_ptr<Tetromino> newTetromino = tetrominoFactory.getRandomTetromino(player.getStartPosition());
	if (newTetromino->checkColision(notActiveTetrominos, DOWN, 200))
	{
		player.setActiveTetromino(newTetromino);
		return true;
	}
	else
	{
		return false;
	}
}

int SingleGame::getLineToClear()
{
	int previousLine = 0, currentLine = 0, brickCounter = 0 ;

	for (std::shared_ptr<Brick> brick : notActiveTetrominos.getBricksList())
	{
		sf::Vector2i brickPosition = brick->getPosition();
		currentLine = brickPosition.y;
		if (currentLine == previousLine)
		{
			brickCounter++;
		}
		if (brickCounter == 9)
		{
			return currentLine;
		}
		previousLine = currentLine;
	}
}

bool SingleGame::checkForInactiveBlock()
{
	cout << "w checku1";
	shared_ptr<Tetromino> activeTetromino = player.getActiveTetromino();
	cout << "w checku2";
	return activeTetromino->checkColision(notActiveTetrominos, DOWN, 200);
}

void SingleGame::moveDownAllActiveBlocks()
{
	player.getActiveTetromino()->moveDown();
}

