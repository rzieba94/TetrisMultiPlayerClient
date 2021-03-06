// TetrisMultiplayerClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TetrominoI.h"
#include "TetrominoFactory.h"
#include "SingleGame.h"
#include <string>
#include "SFML\Network.hpp"
#include "RemoteCmds.h"
#include "LocalPlayer.h"
#include "Cmds.h"
#include "ServerListenerThread.h"
#include <Windows.h>

shared_ptr<LocalPlayer> localPlayer;

bool WINAPI HandlerRoutine(DWORD dwCtrlType)
{
	SimpleCommand msg;
	msg.cmd = Cmds::endServer;
	sf::Packet endPacket;
	endPacket << msg.cmd << msg.winner;
	localPlayer->send(endPacket);
	return dwCtrlType == CTRL_CLOSE_EVENT;
}

using namespace std;

int main()
{

	string serverIp, nick;
	int serverPort;
	bool isConnectionOk = false;

	cout << "TETRIS MULTIPLAYER CLIENT" << endl << endl;
	cout << "Autorzy: " << endl;
	cout << "Marcin Muskala" << endl;
	cout << "Marek Nawrot" << endl;
	cout << "Michal Sliwa" << endl;
	cout << "Rafal Zieba" << endl << endl;

	cout << "Podaj numer ip serwera: ";
	cin >> serverIp;
	cout << "Podaj numer portu dla serwera: ";
	cin >> serverPort;
	cout << "Podaj swoj nick: ";
	cin >> nick;

	shared_ptr<sf::TcpSocket> socket = shared_ptr<sf::TcpSocket>(new sf::TcpSocket);
	sf::Socket::Status status = socket->connect(serverIp, serverPort);
	if (status != sf::Socket::Done)
	{
		cout << "Podczas laczenia z serwerem wystapil blad." << endl;
	}

	sf::Packet packet;
	int cmd = Cmds::connectGame;
	packet << cmd << nick;
	socket->send(packet);
	packet.clear();
	socket->receive(packet);
	ConnectionStatusMsg msg;
	packet >> msg.cmd >> msg.status;
	if (msg.cmd != connStatus || msg.status == "rejected")
	{
		cout << "Podczas laczenia z serwerem wystapil blad" << endl;
	}
	else if (msg.status == "accepted")
	{
		cout << "Nawiazano polaczenie z serwerem gry." << endl;
		isConnectionOk = true;
	}
	if (isConnectionOk)
	{
		localPlayer = shared_ptr<LocalPlayer>(new LocalPlayer(nick, socket));
		ServerListenerThread mainGameListener(localPlayer);
		mainGameListener.launchListeners();
	}
	//string test;
	//cin >> test;

	return 0;
}

