#include "stdafx.h"
#include "CooperationGame.h"
#include "Cmds.h"
#include "RemoteCmds.h"


CooperationGame::CooperationGame(shared_ptr<LocalPlayer> ownerPlayer, vector<string> otherPlayersNicknames) : ParentGameEngine(ownerPlayer)
{
	for (string nick : otherPlayersNicknames)
	{
		if (nick != ownerPlayer->getNick())
		{
			shared_ptr<Player> newPlayer = shared_ptr<Player>(new Player(nick));
			otherPlayers.push_back(newPlayer);
		}
		numOfPlayers++;
		
	}
}


CooperationGame::~CooperationGame()
{

}

void CooperationGame::run()
{
	sf::RenderWindow window(sf::VideoMode(numOfPlayers*200, 400), "Tetris Multiplayer");
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
	}
}

void CooperationGame::placeNewTetromino(sf::Vector2i pos, TetrominoType type, string playerNick)
{
	if (playerNick == localPlayer->getNick()) {
		if (localPlayer->gotFirstBrick)
		{
			shared_ptr<Tetromino> previousTetromino = localPlayer->getActiveTetromino();
			notActiveTetrominos.addTetrisShape(previousTetromino);
		}
		shared_ptr<Tetromino> newTetromino = tetrominoFactory.getTetromino(pos, type);
		localPlayer->setActiveTetromino(newTetromino);
		firstBrick = false;
		localPlayer->gotFirstBrick = true;
	}
	else
	{
		for (shared_ptr<Player> p : otherPlayers)
		{
			if (p->getNick() == playerNick)
			{
				if (p->gotFirstBrick)
				{
					shared_ptr<Tetromino> previousTetromino = p->getActiveTetromino();
					notActiveTetrominos.addTetrisShape(previousTetromino);
				}
				shared_ptr<Tetromino> newTetromino = tetrominoFactory.getTetromino(pos, type);
				p->setActiveTetromino(newTetromino);
				firstBrick = false;
				p->gotFirstBrick = true;
				break;
			}
		}
	}
}

void CooperationGame::forwardMoveCommand(MoveMsg msg)
{
	if (msg.userId == localPlayer->getNick())
	{
		switch (msg.moveType)
		{
		case MoveType::DOWN:
			localPlayer->getActiveTetromino()->moveDown();
			break;
		case MoveType::RIGHT:
			localPlayer->getActiveTetromino()->moveRight();
			break;
		case MoveType::LEFT:
			localPlayer->getActiveTetromino()->moveLeft();
			break;
		case MoveType::ROTATE:
			localPlayer->getActiveTetromino()->rotate();
			break;
		case MoveType::DROP:
			localPlayer->getActiveTetromino()->drop(msg.dropCount);
			break;
		}
		
	}
	else
	{
		for (shared_ptr<Player> p : otherPlayers)
		{
			if (msg.userId == p->getNick() && p->gotFirstBrick)
			{
				switch (msg.moveType)
				{
				case MoveType::DOWN:
					p->getActiveTetromino()->moveDown();
					break;
				case MoveType::RIGHT:
					p->getActiveTetromino()->moveRight();
					break;
				case MoveType::LEFT:
					p->getActiveTetromino()->moveLeft();
					break;
				case MoveType::ROTATE:
					p->getActiveTetromino()->rotate();
					break;
				case MoveType::DROP:
					p->getActiveTetromino()->drop(msg.dropCount);
					break;
				}
				break;
			}
		}
	}
}