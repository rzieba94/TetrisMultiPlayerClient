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
			Player p(nick);
			otherPlayers.push_back(p);
		}
	}
}


CooperationGame::~CooperationGame()
{
}

void CooperationGame::run()
{
	sf::RenderWindow window(sf::VideoMode(800, 400), "Tetris Multiplayer");
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
	for (sf::RectangleShape rectangle : notActiveTetrominos.getDrawableItems())
	{
		window.draw(rectangle);
	}
	for (Player p : otherPlayers)
	{
		Tetromino activeTetromino = *p.getActiveTetromino();
		for (sf::RectangleShape rectangle : activeTetromino.getDrawableItems())
		{
			window.draw(rectangle);
		}
		for (sf::RectangleShape rectangle : notActiveTetrominos.getDrawableItems())
		{
			window.draw(rectangle);
		}
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
		if (!firstBrick)
		{
			shared_ptr<Tetromino> previousTetromino = ownerPlayer->getActiveTetromino();
			notActiveTetrominos.addTetrisShape(previousTetromino);
		}

		shared_ptr<Tetromino> newTetromino = tetrominoFactory.getTetromino(pos, type);
		ownerPlayer->setActiveTetromino(newTetromino);
		firstBrick = false;
	}
	else
	{
		for (Player p : otherPlayers)
		{
			if (p.getNick() == playerNick)
			{
				if (!firstBrick)
				{
					shared_ptr<Tetromino> previousTetromino = ownerPlayer->getActiveTetromino();
					notActiveTetrominos.addTetrisShape(previousTetromino);
				}

				shared_ptr<Tetromino> newTetromino = tetrominoFactory.getTetromino(pos, type);
				ownerPlayer->setActiveTetromino(newTetromino);
				firstBrick = false;
				break;
			}
		}
	}
}

void CooperationGame::moveDownAllActiveBlocks()
{
	ownerPlayer->getActiveTetromino()->moveDown();
	for (Player p : otherPlayers)
	{
		p.getActiveTetromino()->moveDown();
	}
}

void CooperationGame::endGameCloseWindow()
{
	closeWindow = true;
}