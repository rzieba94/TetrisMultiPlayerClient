#pragma once
#include <thread>
#include "TetrominosGroup.h"
#include "TetrominoFactory.h"
#include "LocalPlayer.h"
#include "Player.h"
#include <memory>
#include <thread>
#include <ctime>
#include <iostream>
#include "RemoteCmds.h"
#include "Cmds.h"

class ParentGameEngine
{
public:
	ParentGameEngine(shared_ptr<LocalPlayer> ownerPlayer);
	virtual ~ParentGameEngine();
	void startThread();
	void clearLine(int lineNumber);
	virtual void run() = 0;
	void endGameCloseWindow();
protected:
	void displayInWindow(sf::RenderWindow & window);
	void checkPlayersMove(sf::RenderWindow & window);

	shared_ptr<LocalPlayer> localPlayer;
	list<shared_ptr<Player>> otherPlayers;
	bool firstBrick;
	bool closeWindow;
	int numOfPlayers = 0;
	TetrominoFactory tetrominoFactory;
	std::thread gameThread;
	clock_t startTime;
	TetrominosGroup notActiveTetrominos;
	static const int FRAME_DURATION = 1000;
};

