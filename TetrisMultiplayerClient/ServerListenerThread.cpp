#include "stdafx.h"
#include "ServerListenerThread.h"
#include "RemoteCmds.h"
#include "Cmds.h"
#include <thread>
#include <iostream>
#include <sstream>
#include <string>
#include "SingleGame.h"
#include "StringSplitter.h"


ServerListenerThread::ServerListenerThread(shared_ptr<LocalPlayer> localPlayer) : localPlayer(localPlayer), isRunning(true)
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
			StartGame msg;
			incomingPacket >> msg.gameType >> msg.playersNumber >> msg.userIds;
			cout << msg.gameType << msg.playersNumber << msg.userIds;
			if (msg.gameType == GameType::single)
			{
				
				std::vector<std::string> playerNames = StringSplitter::split(msg.userIds, ';');
				Player singleGamePlayer(playerNames[0]);
				SingleGame game(singleGamePlayer);
				game.startThread();
			}
			else
			{
				//multi
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
		
		std::this_thread::sleep_for(std::chrono::microseconds(100));
	}
}