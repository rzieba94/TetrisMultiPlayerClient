#include "stdafx.h"
#include "SingleGame.h"
#include <thread>
#include <iostream>
#include "RemoteCmds.h"
#include "Cmds.h"

using namespace std;

SingleGame::SingleGame(shared_ptr<LocalPlayer> ownerPlayer) : ParentGameEngine(ownerPlayer)
{
	
}

SingleGame::~SingleGame()
{
}

void SingleGame::run()
{
	sf::RenderWindow window(sf::VideoMode(200, 400), "Tetris Multiplayer");
	window.setActive(true);
	while (window.isOpen())
	{
		if (!firstBrick) {
			displayInWindow(window);
			checkPlayersMove(window);
		}
		if (closeWindow)
		{
			window.close();
		}
		this_thread::sleep_for(chrono::milliseconds(10));
	}
}

void SingleGame::placeNewTetromino(sf::Vector2i pos, TetrominoType type)
{
	if (!firstBrick)
	{
		shared_ptr<Tetromino> previousTetromino = localPlayer->getActiveTetromino();
		notActiveTetrominos.addTetrisShape(previousTetromino);
	}

	shared_ptr<Tetromino> newTetromino = tetrominoFactory.getTetromino(pos, type);
	localPlayer->setActiveTetromino(newTetromino);
	firstBrick = false;
}
