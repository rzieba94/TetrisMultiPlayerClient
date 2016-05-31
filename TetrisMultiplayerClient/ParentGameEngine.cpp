#include "stdafx.h"
#include "ParentGameEngine.h"
#include <iostream>

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
