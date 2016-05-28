#include "stdafx.h"
#include "SingleGame.h"
#include <thread>

using namespace std;

SingleGame::SingleGame(Player player) : player(player)
{
}


SingleGame::~SingleGame()
{
}

void SingleGame::run()
{
	sf::RenderWindow window(sf::VideoMode(200, 400), "Tetris Multiplayer");
	window.setActive(true);
	placeNewTetromino();
	while (window.isOpen())
	{
		checkPlayersMove(window);
		notActiveTetrominos.clearLine(getLineToClear());
		if (checkForInactiveBlock())
		{
			if (!placeNewTetromino())
			{
				return;
			}
		}
		
		displayInWindow(window);

		checkFrameTime();
		this_thread::sleep_for(chrono::milliseconds(10));
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
			shared_ptr<Tetromino> activeTetromino = player.getActiveTetromino();
			if (event.key.code == sf::Keyboard::Right)
			{
				if (!activeTetromino->checkColision(notActiveTetrominos, RIGHT, 200))
				{
					activeTetromino->moveRight();
				}
			}
			else if (event.key.code == sf::Keyboard::Left)
			{
				if (!activeTetromino->checkColision(notActiveTetrominos, LEFT, 200))
				{
					activeTetromino->moveLeft();
				}
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				if (!activeTetromino->checkColision(notActiveTetrominos, DOWN, 200))
				{
					activeTetromino->moveDown();
				}
			}
			else if (event.key.code == sf::Keyboard::Up)
			{
				if (!activeTetromino->checkColision(notActiveTetrominos, ROTATE, 200))
				{
					activeTetromino->rotate();
				}
			}
			else if (event.key.code == sf::Keyboard::Space)
			{
				int dropAmount = activeTetromino->getDropCount(notActiveTetrominos, 200);
				activeTetromino->drop(dropAmount);
			}
		}
	}
}

bool SingleGame::placeNewTetromino()
{
	shared_ptr<Tetromino> newTetromino = tetrominoFactory.getRandomTetromino(player.getStartPosition());
	if (!newTetromino->checkColision(notActiveTetrominos, DOWN, 200))
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

	list<shared_ptr<Brick>> bricksList = notActiveTetrominos.getBricksList();
	vector <int> bricksInRowsCounter(20, 0);
	
	for (shared_ptr<Brick> brick : notActiveTetrominos.getBricksList())
	{
		sf::Vector2i brickPosition = brick->getPosition();
		int brickRow = brickPosition.y / Brick::BRICK_SIZE;
		bricksInRowsCounter[brickRow]++;
	}

	for (int lineNo = 0; lineNo < bricksInRowsCounter.size() ; lineNo++)
	{
		if (bricksInRowsCounter[lineNo] == 10)
		{
			return lineNo;
		}
	}
	return -1;
}

bool SingleGame::checkForInactiveBlock()
{
	shared_ptr<Tetromino> activeTetromino = player.getActiveTetromino();
	if (activeTetromino->checkColision(notActiveTetrominos, DOWN, 200))
	{
		notActiveTetrominos.addTetrisShape(activeTetromino);
		return true;
	}
	else
	{
		return false;
	}
}

void SingleGame::moveDownAllActiveBlocks()
{
	player.getActiveTetromino()->moveDown();
}

