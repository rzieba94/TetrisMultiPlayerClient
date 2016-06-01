#pragma once
#include "LocalPlayer.h"
#include "SingleGame.h"
#include <memory>

class ServerListenerThread
{
public:
	ServerListenerThread(shared_ptr<LocalPlayer> localPlayer);
	~ServerListenerThread();
	void launchListeners();
private:
	shared_ptr<LocalPlayer> localPlayer;
	SingleGame *singleGame;
	bool isRunning;
	bool singleplayer;
	void runServerListener();
	void runClientListener();

};

