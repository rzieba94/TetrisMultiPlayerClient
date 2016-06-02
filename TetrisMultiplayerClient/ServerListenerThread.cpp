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
			else
			{
				//MULTI
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
				if (singleplayer)
				{
					localPlayer->getActiveTetromino()->moveRight();
				}
				else
				{
					//MULTI
				}
				break;
			case MoveType::LEFT:
				if (singleplayer)
				{
					localPlayer->getActiveTetromino()->moveLeft();
				}
				else
				{
					//MULTI
				}
				break;
			case MoveType::DOWN:
				if (singleplayer)
				{
					localPlayer->getActiveTetromino()->moveDown();
				}
				else
				{
					//MULTI
				}
				break;
			case MoveType::ROTATE:
				if (singleplayer)
				{
					localPlayer->getActiveTetromino()->rotate();
				}
				else
				{
					//MULTI
				}
				break;
			case MoveType::DROP:
				if (singleplayer)
				{
					localPlayer->getActiveTetromino()->drop(msg.dropCount);
				}
				else
				{
					//MULTI
				}
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
			if (!singleplayer) {
		case Cmds::userLost:
		{
			sendUserLost lost;
			incomingPacket >> lost.nick >> lost.score;
			cout << "Gracz " << lost.nick << " zakonczyl gre z wynikiem " << lost.score << " punktow!" << endl;
		}
		break;
			}
		case Cmds::endGame:
			isRunning = false;
			bool winner = false;
			incomingPacket >> winner;
			if (singleplayer)
			{
				singleGame->endGameCloseWindow();
				delete(singleGame);
			}
			else
			{
				coopGame->endGameCloseWindow();
				delete(coopGame);
			}
			if (!winner)
			{
				cout << "Koniec gry " << localPlayer->getNick() << "! Uzyskales " << localPlayer->getScore() << " punktow!" << endl;
			}
			else
			{
				cout << "Wygrales " << localPlayer->getNick() << "! Uzyskales " << localPlayer->getScore() << " punktow!" << endl;
			}
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
	bool startingNewGame = false;
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
		startingNewGame = true;
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
				startingNewGame = true;
				isRunning = true;
				msg.gameType = GameType::cooperation;
				msg.playersNumber = numCommand;
				msg.userIds = localPlayer->getNick() + ";";
			}
		}
		else
		{
			GamesList glist;
			glist.cmd = Cmds::getGamesList;
			sf::Packet pack;
			pack << glist.cmd;
			localPlayer->send(pack);
			pack.clear();
			pack = localPlayer->receive();
			int gMsg;
			pack >> gMsg;
			if (gMsg == Cmds::getGamesList)
			{
				pack >> glist.gamesIds >> glist.nickNames;
				cout << "Lista dostepnych gier. Aby doloczyc wpisz id gry." << endl;
				cout << "ID |  GRACZE" << endl;;
				vector<string> ids = StringSplitter::split(glist.gamesIds, ';');
				vector<string> nicknames = StringSplitter::split(glist.nickNames, '|');
				int i = 0;
				for (string id : ids)
				{
					cout << id <<"  |  " << nicknames[i++] << endl;
				}
				int selectedID = -1;
				cin >> selectedID;
				ConnectToGame connectMsg;
				connectMsg.cmd = Cmds::connectToGame;
				connectMsg.gameId = selectedID;
				sf::Packet connectPacket;
				connectPacket.clear();
				connectPacket << connectMsg.cmd << connectMsg.gameId;
				localPlayer->send(connectPacket);
			}
		}
		
	}
	else
	{
		msg.cmd = Cmds::endGame;
		isRunning = false;
	}

	if (startingNewGame)
	{
		gameStartPacket << msg.cmd << msg.gameType << msg.playersNumber << msg.userIds;
		localPlayer->send(gameStartPacket);
	}

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
				vector<string> otherPlayersNicks = StringSplitter::split(msg.userIds, ';');
				coopGame = new CooperationGame(localPlayer, otherPlayersNicks);
				thread coopGameThread(&CooperationGame::run, coopGame);
				thread serverListener(&ServerListenerThread::runServerListener, this);
				coopGameThread.join();
				serverListener.join();
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
		/*
		else
		{
			gameStarted = true;
			cout << "POLACZENIE Z SERWEREM ZOSTALO PRZERWANE, APLIKACJA ZOSTANIE ZAMKNIETA" << endl;
			std::cin.ignore();
			std::cin.ignore();
		}*/
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}