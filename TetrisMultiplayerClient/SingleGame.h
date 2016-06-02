#pragma once
#include "ParentGameEngine.h"

using namespace std;

class SingleGame : public ParentGameEngine
{
public:
	SingleGame(shared_ptr<LocalPlayer> ownerPlayer);
	~SingleGame();
	void placeNewTetromino(sf::Vector2i pos,TetrominoType type);
	void run();
};

