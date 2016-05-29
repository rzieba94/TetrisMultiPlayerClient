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

using namespace std;

int main()
{
	string serverIp, nick;
	int serverPort;

	cout << "TETRIS MULTIPLAYER SERVER" << endl << endl;
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
		cout << "Podczas laczenia z serwerem wystapil blad.";
	}

	sf::Packet packet;
	string cmd = "connect";
	packet << cmd << nick;
	socket->send(packet);
	packet.clear();
	socket->receive(packet);
	ConnectionStatusMsg msg;
	packet >> msg.cmd >> msg.status;
	if (msg.cmd != "connStatus" || msg.status == "rejected")
	{
		cout << "Podczas laczenia z serwerem wystapil blad";
	}
	else if (msg.status == "accepted")
	{
		cout << "Nawiazano polaczenie z serwerem gry.";
	}
	shared_ptr<LocalPlayer> localPlayer = shared_ptr<LocalPlayer>(new LocalPlayer(nick, socket));
	string test;
	cin >> test;

	return 0;
}

