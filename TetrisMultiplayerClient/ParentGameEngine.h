#pragma once
#include <thread>
#include "TetrominosGroup.h"
#include "TetrominoFactory.h"
#include <memory>
#include <thread>
#include <ctime>

class ParentGameEngine
{
public:
	ParentGameEngine();
	virtual ~ParentGameEngine();
	void startThread();
protected:
	virtual void run() = 0;
	void checkFrameTime();
	virtual void moveDownAllActiveBlocks() = 0;
	virtual void displayInWindow(sf::RenderWindow & window) = 0;

	TetrominoFactory tetrominoFactory;
	std::thread gameThread;
	clock_t startTime;
	TetrominosGroup notActiveTetrominos;
	static const int FRAME_DURATION = 1000;
};

