#pragma once
#include "LocalPlayer.h";
#include <memory>

class ServerListenerThread
{
public:
	ServerListenerThread(shared_ptr<LocalPlayer> localPlayer);
	~ServerListenerThread();
private:
	shared_ptr<LocalPlayer> localPlayer;
};

