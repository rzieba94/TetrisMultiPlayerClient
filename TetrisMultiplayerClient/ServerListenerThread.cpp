#include "stdafx.h"
#include "ServerListenerThread.h"


ServerListenerThread::ServerListenerThread(shared_ptr<LocalPlayer> localPlayer) : localPlayer(localPlayer)
{
}


ServerListenerThread::~ServerListenerThread()
{
}
