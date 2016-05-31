#pragma once
#include "ParentGameEngine.h"
#include "LocalPlayer.h"

using namespace std;

class SingleGame : public ParentGameEngine
{
public:
	SingleGame();
	SingleGame(shared_ptr<LocalPlayer> player);
	~SingleGame();
	bool placeNewTetromino(sf::Vector2i pos,TetrominoType type);
	void run();
private:
	
	void displayInWindow(sf::RenderWindow & window);
	void moveDownAllActiveBlocks();
	int getLineToClear();
	bool checkForInactiveBlock();
	void checkPlayersMove(sf::RenderWindow & window);
	shared_ptr<LocalPlayer> player;
	bool firstBrick;
};

