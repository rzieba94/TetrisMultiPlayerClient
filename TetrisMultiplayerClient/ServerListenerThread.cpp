#include "stdafx.h"
#include "ServerListenerThread.h"
#include "RemoteCmds.h"
#include "Cmds.h"
#include <thread>
#include <iostream>
#include <sstream>
#include <string>
#include "StringSplitter.h"



ServerListenerThread::ServerListenerThread(shared_ptr<LocalPlayer> localPlayer) : localPlayer(localPlayer), isRunning(true), gameStarted(false)
{
}

ServerListenerThread::~ServerListenerThread()
{
}

void ServerListenerThread::launchListeners()
{
	thread serverListener(&ServerListenerThread::runServerListener, this);
	thread clientListener(&ServerListenerThread::runClientListener, this);
	serverListener.join();
	clientListener.join();
}

void ServerListenerThread::runServerListener()
{
	sf::Packet incomingPacket;
	int servMsg;
	while (isRunning)
	{
		incomingPacket.clear();
		incomingPacket = localPlayer->receive();
		servMsg = -1;
		incomingPacket >> servMsg;
		switch (servMsg)
		{
		case Cmds::startGame:
		{
			singleGame = new SingleGame(*localPlayer);
			gameStarted = true;
			StartGame msg;
			incomingPacket >> msg.gameType >> msg.playersNumber >> msg.userIds;
			cout << msg.gameType << msg.playersNumber << msg.userIds;
			if (msg.gameType == GameType::single)
			{
				singleplayer = true;
			}
			else
			{
				//multi
				singleplayer = false;
			}
		}
			break;
		case Cmds::placeTetromino:
		{
			PlaceTetromino msg;
			incomingPacket >> msg.tetrominoType >> msg.userId >> msg.positionX >> msg.positionY;
			cout << "odebrany klocek" << endl;
			if (singleplayer)
			{
				sf::Vector2i tetPos(msg.positionX, msg.positionY);
				singleGame->placeNewTetromino(tetPos, (TetrominoType)msg.tetrominoType);
			}
		}
			break;
		case Cmds::move:
		{
			MoveMsg msg;
			incomingPacket >> msg.moveType >> msg.userId >> msg.dropCount;
			switch (msg.moveType)
			{
			case MoveType::RIGHT:
				localPlayer->getActiveTetromino()->moveRight();
				break;
			case MoveType::LEFT:
				localPlayer->getActiveTetromino()->moveLeft();
				break;
			case MoveType::DOWN:
				localPlayer->getActiveTetromino()->moveDown();
				break;
			case MoveType::ROTATE:
				localPlayer->getActiveTetromino()->rotate();
				break;
			case MoveType::DROP:
				localPlayer->getActiveTetromino()->drop(msg.dropCount);
				break;
			}
		}
			break;
		case Cmds::endGame:
			isRunning = false;
			break;
		default:
			break;
		}
		std::this_thread::sleep_for(std::chrono::microseconds(100));
	}
}

void ServerListenerThread::runClientListener()
{

	int numCommand;

	cout << endl << "Gra jednoosobowa - 1" << endl << "Gra wieloosobowa - 2" << endl;	
	cin >> numCommand;


	sf::Packet gameStartPacket;
	gameStartPacket.clear();
	StartGame msg;
	msg.cmd = startGame;
	if (numCommand == 1)
	{
		msg.gameType = GameType::single;
		msg.playersNumber = 1;
		msg.userIds = "1;";
	}
	else if (numCommand == 2)
	{

	}
	else
	{
		isRunning = false;
	}
	gameStartPacket << msg.cmd << msg.gameType << msg.playersNumber << msg.userIds;
	localPlayer->send(gameStartPacket);

	while (isRunning)
	{
		if (gameStarted)
		{
			//TODO: ZWRACA NULLA POPRAWIC
			sf::RenderWindow *window = singleGame->getWindow();
			sf::Event event;
			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window->close();
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

		std::this_thread::sleep_for(std::chrono::microseconds(100));
	}
}