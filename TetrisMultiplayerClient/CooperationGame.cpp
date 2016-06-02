#include "stdafx.h"
#include "CooperationGame.h"
#include "Cmds.h"
#include "RemoteCmds.h"


CooperationGame::CooperationGame(shared_ptr<LocalPlayer> ownerPlayer, vector<string> otherPlayersNicknames) : ownerPlayer(ownerPlayer), firstBrick(true), closeWindow(false)
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

void CooperationGame::displayInWindow(sf::RenderWindow & window)
{
	window.clear();
	Tetromino activeTetromino = *ownerPlayer->getActiveTetromino();
	for (sf::RectangleShape rectangle : activeTetromino.getDrawableItems())
	{
		window.draw(rectangle);
	}
	for (shared_ptr<Player> p : otherPlayers)
	{
		if (p->gotFirstBrick) {
			shared_ptr<Tetromino> remotePlayerTetromino = p->getActiveTetromino();
			for (sf::RectangleShape rectangle : remotePlayerTetromino->getDrawableItems())
			{
				window.draw(rectangle);
			}
		}
	}
	for (sf::RectangleShape rectangle : notActiveTetrominos.getDrawableItems())
	{
		window.draw(rectangle);
	}
	window.display();
}

void CooperationGame::checkPlayersMove(sf::RenderWindow & window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			SimpleCommand msg;
			msg.cmd = Cmds::endGame;
			sf::Packet closePacket;
			closePacket << msg.cmd;
			ownerPlayer->send(closePacket);
			window.close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			MoveMsg msg;
			msg.cmd = Cmds::move;
			msg.userId = ownerPlayer->getNick();
			msg.dropCount = 0;
			if (event.key.code == sf::Keyboard::Right)
			{
				msg.moveType = MoveType::RIGHT;
			}
			else if (event.key.code == sf::Keyboard::Left)
			{
				msg.moveType = MoveType::LEFT;
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				msg.moveType = MoveType::DOWN;
			}
			else if (event.key.code == sf::Keyboard::Up)
			{
				msg.moveType = MoveType::ROTATE;
			}
			else if (event.key.code == sf::Keyboard::Space)
			{
				msg.moveType = MoveType::DROP;
			}
			sf::Packet movePacket;
			movePacket.clear();
			movePacket << msg.cmd << msg.moveType << msg.userId << msg.dropCount;
			ownerPlayer->send(movePacket);
		}
	}
}

void CooperationGame::placeNewTetromino(sf::Vector2i pos, TetrominoType type, string playerNick)
{
	if (playerNick == ownerPlayer->getNick()) {
		if (ownerPlayer->gotFirstBrick)
		{
			shared_ptr<Tetromino> previousTetromino = ownerPlayer->getActiveTetromino();
			notActiveTetrominos.addTetrisShape(previousTetromino);
		}
		shared_ptr<Tetromino> newTetromino = tetrominoFactory.getTetromino(pos, type);
		ownerPlayer->setActiveTetromino(newTetromino);
		firstBrick = false;
		ownerPlayer->gotFirstBrick = true;
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

void CooperationGame::moveDownAllActiveBlocks()
{
	ownerPlayer->getActiveTetromino()->moveDown();
	for (shared_ptr<Player> p : otherPlayers)
	{
		p->getActiveTetromino()->moveDown();
	}
}

void CooperationGame::endGameCloseWindow()
{
	closeWindow = true;
}

void CooperationGame::forwardMoveCommand(MoveMsg msg)
{
	if (msg.userId == ownerPlayer->getNick())
	{
		switch (msg.moveType)
		{
		case MoveType::DOWN:
			ownerPlayer->getActiveTetromino()->moveDown();
			break;
		case MoveType::RIGHT:
			ownerPlayer->getActiveTetromino()->moveRight();
			break;
		case MoveType::LEFT:
			ownerPlayer->getActiveTetromino()->moveLeft();
			break;
		case MoveType::ROTATE:
			ownerPlayer->getActiveTetromino()->rotate();
			break;
		case MoveType::DROP:
			ownerPlayer->getActiveTetromino()->drop(msg.dropCount);
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