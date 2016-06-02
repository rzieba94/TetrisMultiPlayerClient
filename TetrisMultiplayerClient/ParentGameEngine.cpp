#include "stdafx.h"
#include "ParentGameEngine.h"

using namespace std;

ParentGameEngine::ParentGameEngine(shared_ptr<LocalPlayer> ownerPlayer) : notActiveTetrominos(sf::Vector2i(100, 200)), 
	tetrominoFactory(), localPlayer(ownerPlayer), firstBrick(true), closeWindow(false), otherPlayers()
{
	this->startTime = clock();
}

ParentGameEngine::~ParentGameEngine()
{
}


void ParentGameEngine::startThread()
{
	gameThread = thread(&ParentGameEngine::run, this);
}

void ParentGameEngine::clearLine(int lineNumber)
{
	notActiveTetrominos.clearLine(lineNumber);
}

void ParentGameEngine::endGameCloseWindow()
{
	closeWindow = true;
}


void ParentGameEngine::checkPlayersMove(sf::RenderWindow & window)
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
			localPlayer->send(closePacket);
			window.close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			MoveMsg msg;
			msg.cmd = Cmds::move;
			msg.userId = localPlayer->getNick();
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
			localPlayer->send(movePacket);
		}
	}
}

void ParentGameEngine::displayInWindow(sf::RenderWindow & window)
{
	window.clear();
	Tetromino activeTetromino = *localPlayer->getActiveTetromino();
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