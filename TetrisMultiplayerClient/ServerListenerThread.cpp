#include "stdafx.h"
#include "ServerListenerThread.h"
#include "RemoteCmds.h"
#include "Cmds.h"
#include <thread>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include "StringSplitter.h"
#include <cstdio>



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
		case Cmds::clearLine:
		{
			ClearLine msg;
			incomingPacket >> msg.lineNumber;
			singleGame->clearLine(msg.lineNumber);
		}
			break;
		case Cmds::addScore:
		{
			AddScore msg;
			incomingPacket >> msg.score;
			localPlayer->addScore(msg.score);
		}
			break;
		case Cmds::endGame:
			isRunning = false;
			singleGame->endGameCloseWindow();
			delete(singleGame);
			cout << "Koniec gry " << localPlayer->getNick() << "! Uzyskales " << localPlayer->getScore() << " punktow!" << endl;
			break;
		default:
			break;
		}
		std::this_thread::sleep_for(std::chrono::microseconds(100));
	}
	cout << "Wcisnij enter aby wrocic do menu" << endl;
	std::cin.ignore();
	std::cin.ignore();
	system("cls");
	runClientListener();
}

void ServerListenerThread::runClientListener()
{
	int numCommand;
	cout << "ROZPOCZNIJ NOWA GRE";
	cout << endl << "Gra jednoosobowa - 1" << endl << "Gra wieloosobowa - 2" << endl;	
	cin >> numCommand;
	sf::Packet gameStartPacket;
	gameStartPacket.clear();
	StartGame msg;
	msg.cmd = startGame;
	if (numCommand == 1)
	{
		isRunning = true;
		msg.gameType = GameType::single;
		msg.playersNumber = 1;
		msg.userIds = localPlayer->getNick() + ";";
	}
	else if (numCommand == 2)
	{
		cout << endl << "Zaloz gre - 1" << endl << "Dolacz do gry - 2" << endl;
		cin >> numCommand;
		if (numCommand == 1)
		{
			cout << endl << "Podaj liczbê graczy (max 4)" << endl;
			cin >> numCommand;
			if(numCommand <= 4)
			{
				isRunning = true;
				msg.gameType = GameType::cooperation;
				msg.playersNumber = numCommand;
				msg.userIds = localPlayer->getNick() + ";";
			}
		}
		
	}
	else
	{
		msg.cmd = Cmds::endGame;
		isRunning = false;
	}
	gameStartPacket << msg.cmd << msg.gameType << msg.playersNumber << msg.userIds;
	localPlayer->send(gameStartPacket);

	bool gameStarted = false;
	int lastTime = -1;
	while (!gameStarted)
	{
		gameStartPacket.clear();
		gameStartPacket = localPlayer->receive();
		int servMsg = -1;
		gameStartPacket >> servMsg;
		if (servMsg == Cmds::startGame) {
			StartGame msg;
			gameStartPacket >> msg.gameType >> msg.playersNumber >> msg.userIds;
			if (msg.gameType == GameType::single)
			{
				gameStarted = true;
				singleplayer = true;
				singleGame = new SingleGame(localPlayer);
				thread singleGameThread(&SingleGame::run, singleGame);
				thread serverListener(&ServerListenerThread::runServerListener, this);
				singleGameThread.join();
				serverListener.join();
			}
			else if (msg.gameType == GameType::cooperation)
			{
				gameStarted = true;
				singleplayer = false;
				//coop
			}
		}
		else if (servMsg == Cmds::waiting)
		{
			
			WaitingTime msg;
			gameStartPacket >> msg.waitingtime;
			if (msg.waitingtime % 10 == 0 && msg.waitingtime != lastTime)
			{
				lastTime = msg.waitingtime;
				cout << "Oczekiwanie na graczy. Pozostaly czas: " << msg.waitingtime << endl;
			}
		}
		else if(servMsg == Cmds::timeout)
		{ 
			gameStarted = true;
			SimpleCommand msg;
			msg.cmd = Cmds::endGame;
			sf::Packet closePacket;
			closePacket << msg.cmd;
			localPlayer->send(closePacket);
			cout << "Zbyt d³ugi czas oczekiwania. Wcisnij enter aby wrocic do menu." << endl;
			std::cin.ignore();
			std::cin.ignore();
			system("cls");
			runClientListener();
		}
		else
		{
			gameStarted = true;
			cout << "POLACZENIE Z SERWEREM ZOSTALO PRZERWANE, APLIKACJA ZOSTANIE ZAMKNIETA" << endl;
			std::cin.ignore();
			std::cin.ignore();
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}