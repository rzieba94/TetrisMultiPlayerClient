#include "stdafx.h"
#include "SingleGame.h"
#include <thread>
#include <iostream>
#include "RemoteCmds.h"
#include "Cmds.h"

using namespace std;

SingleGame::SingleGame(shared_ptr<LocalPlayer> player) : player(player), firstBrick(true), closeWindow(false)
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

void SingleGame::displayInWindow(sf::RenderWindow & window)
{
	window.clear();
	Tetromino activeTetromino = *player->getActiveTetromino();
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

void SingleGame::clearLine(int lineNumber)
{
	notActiveTetrominos.clearLine(lineNumber);
}

void SingleGame::endGameCloseWindow()
{
	closeWindow = true;
}


void SingleGame::checkPlayersMove(sf::RenderWindow & window)
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
			player->send(closePacket);
			window.close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			MoveMsg msg;
			msg.cmd = Cmds::move;
			msg.userId = player->getNick();
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
			player->send(movePacket);
		}
	}
}

void SingleGame::placeNewTetromino(sf::Vector2i pos, TetrominoType type)
{
	if (!firstBrick)
	{
		shared_ptr<Tetromino> previousTetromino = player->getActiveTetromino();
		notActiveTetrominos.addTetrisShape(previousTetromino);
	}

	shared_ptr<Tetromino> newTetromino = tetrominoFactory.getTetromino(pos, type);
	player->setActiveTetromino(newTetromino);
	firstBrick = false;
}

void SingleGame::moveDownAllActiveBlocks()
{
	player->getActiveTetromino()->moveDown();
}
