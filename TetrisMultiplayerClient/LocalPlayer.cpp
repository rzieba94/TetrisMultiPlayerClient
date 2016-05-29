#include "stdafx.h"
#include "LocalPlayer.h"


LocalPlayer::LocalPlayer(string nick) : Player(nick)
{
}


LocalPlayer::~LocalPlayer()
{
}

void LocalPlayer::send(sf::Packet packet)
{
	socket->send(packet);
}

sf::Packet LocalPlayer::receive()
{
	sf::Packet packet;
	socket->receive(packet);
	return packet;
}