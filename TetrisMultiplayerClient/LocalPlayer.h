#pragma once
#include "Player.h"
#include "stdafx.h"
#include "SFML\Network.hpp"

class LocalPlayer : public Player
{
public:
	LocalPlayer(string nick);
	~LocalPlayer();
	void send(sf::Packet packet);
	sf::Packet receive();
private:
	shared_ptr<sf::TcpSocket> socket;
};

