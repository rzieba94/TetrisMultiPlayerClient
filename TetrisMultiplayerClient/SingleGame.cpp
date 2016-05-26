#include "stdafx.h"
#include "SingleGame.h"
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
		if (checkForInactiveBlock())
		{
			if (!placeNewTetromino())
			{
				return;
			}
		}
		displayInWindow(*window);
		checkFrameTime();
		this_thread::sleep_for(chrono::milliseconds(500));
	}
}

void SingleGame::displayInWindow(sf::RenderWindow & window)
{
	window.clear();
	Tetromino activeTetromino = *player.getActiveTetromino();
	for (sf::RectangleShape rectangle : activeTetromino.getDrawableItems())
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
			Tetromino activeTetromino = *player.getActiveTetromino();
			if (event.key.code == sf::Keyboard::Right)
			{
				if (!activeTetromino.checkColision(notActiveTetrominos, RIGHT, 200))
				{
					activeTetromino.moveRight();
				}
			}
			else if (event.key.code == sf::Keyboard::Left)
			{
				if (!activeTetromino.checkColision(notActiveTetrominos, LEFT, 200))
				{
					activeTetromino.moveLeft();
				}
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				if (!activeTetromino.checkColision(notActiveTetrominos, DOWN, 200))
				{
					activeTetromino.moveDown();
				}
			}
			else if (event.key.code == sf::Keyboard::Up)
			{
				if (!activeTetromino.checkColision(notActiveTetrominos, ROTATE, 200))
				{
					activeTetromino.rotate();
				}
			}
			else if (event.key.code == sf::Keyboard::Space)
			{
				int dropAmount = activeTetromino.getDropCount(notActiveTetrominos, 200);
				activeTetromino.drop(dropAmount);
			}
		}
	}
}

bool SingleGame::placeNewTetromino()
{
	Tetromino newTetromino = tetrominoFactory.getRandomTetromino(player.getStartPosition());
	if (!newTetromino.checkColision(notActiveTetrominos, DOWN, 200))
	{
		player.setActiveTetromino(&newTetromino);
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

	list<shared_ptr<Brick>> bricksList = notActiveTetrominos.getBricksList();
	if (!bricksList.empty())
	{
		for (shared_ptr<Brick> brick : notActiveTetrominos.getBricksList())
		{
			sf::Vector2i brickPosition = brick->getPosition();
			currentLine = brickPosition.y;
			if (currentLine == previousLine)
			{
				brickCounter++;
			}
			else
			{
				brickCounter = 0;
			}
			if (brickCounter == 9)
			{
				return currentLine;
			}
			previousLine = currentLine;
		}
	}
	return -1;
}

bool SingleGame::checkForInactiveBlock()
{
	Tetromino activeTetromino = *player.getActiveTetromino();
	return activeTetromino.checkColision(notActiveTetrominos, DOWN, 200);
}

void SingleGame::moveDownAllActiveBlocks()
{
	player.getActiveTetromino()->moveDown();
}

