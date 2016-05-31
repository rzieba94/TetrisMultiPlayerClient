#include "stdafx.h"
#include "ServerListenerThread.h"
#include "RemoteCmds.h"
#include "Cmds.h"
#include <thread>
#include <iostream>
#include <sstream>
#include <string>
#include "StringSplitter.h"



ServerListenerThread::ServerListenerThread(shared_ptr<LocalPlayer> localPlayer) : localPlayer(localPlayer), isRunning(true)
{
}

ServerListenerThread::~ServerListenerThread()
{
}

void ServerListenerThread::launchListeners()
{
	runClientListener();
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
		case Cmds::placeTetromino:
		{
			PlaceTetromino msg;
			incomingPacket >> msg.tetrominoType >> msg.userId >> msg.positionX >> msg.positionY;
			cout << "odebrany klocek" << endl;
			if (singleplayer)
			{
				sf::Vector2i tetPos((msg.positionX * Brick::BRICK_SIZE), (msg.positionY * Brick::BRICK_SIZE));
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

	gameStartPacket.clear();
	gameStartPacket = localPlayer->receive();
	int servMsg = -1;
	gameStartPacket >> servMsg;
	if (servMsg == Cmds::startGame) {
		StartGame msg;
		gameStartPacket >> msg.gameType >> msg.playersNumber >> msg.userIds;
		cout << msg.gameType << msg.playersNumber << msg.userIds;
		if (msg.gameType == GameType::single)
		{
			singleplayer = true;
			singleGame = new SingleGame(localPlayer);
			thread singleGameThread(&SingleGame::run, singleGame);
			thread serverListener(&ServerListenerThread::runServerListener, this);
			singleGameThread.join();
			serverListener.join();
		}
		else
		{
			//multi
			singleplayer = false;
		}
	}
}