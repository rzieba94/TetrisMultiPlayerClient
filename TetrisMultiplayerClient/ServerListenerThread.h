#pragma once
#include "LocalPlayer.h";
#include <memory>

class ServerListenerThread
{
public:
	ServerListenerThread(shared_ptr<LocalPlayer> localPlayer);
	~ServerListenerThread();
	void launchListeners();
private:
	shared_ptr<LocalPlayer> localPlayer;
	bool isRunning;
	void runServerListener();
	void runClientListener();
};

