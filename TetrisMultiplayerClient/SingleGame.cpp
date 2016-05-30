#include "stdafx.h"
#include "SingleGame.h"
#include <thread>
#include <iostream>


using namespace std;

SingleGame::SingleGame()
{
}

SingleGame::SingleGame(Player player) : player(player), firstBrick(true)
{
	window = sf::RenderWindow(sf::VideoMode(200, 400), "Tetris Multiplayer");
}

SingleGame::~SingleGame()
{
}

void SingleGame::run()
{

	window->setActive(true);
	while (window->isOpen())
	{
		displayInWindow(*window);
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
	
}

bool SingleGame::placeNewTetromino(sf::Vector2i pos, TetrominoType type)
{
	shared_ptr<Tetromino> newTetromino = tetrominoFactory.getTetromino(pos, type);
	if (!newTetromino->checkColision(notActiveTetrominos, DOWN, 200))
	{
		player.setActiveTetromino(newTetromino);
		if (firstBrick)
		{
			firstBrick = false;
			run();
			cout << "odpalamy";
		}
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

sf::RenderWindow *SingleGame::getWindow()
{
	return window;
}
