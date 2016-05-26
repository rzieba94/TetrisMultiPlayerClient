#include "stdafx.h"
#include "ParentGameEngine.h"

using namespace std;

ParentGameEngine::ParentGameEngine() : notActiveTetrominos(sf::Vector2i(100, 200)), tetrominoFactory()
{
	this->startTime = clock();
}


ParentGameEngine::~ParentGameEngine()
{
}


void ParentGameEngine::startThread()
{
	gameThread = thread(&ParentGameEngine::run, this);
}

void ParentGameEngine::checkFrameTime()
{
	if (clock() - startTime > FRAME_DURATION)
	{
		moveDownAllActiveBlocks();
		startTime = clock();
	}
}
