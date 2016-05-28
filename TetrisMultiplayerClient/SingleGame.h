#pragma once
#include "ParentGameEngine.h"
#include "Player.h"

using namespace std;

class SingleGame : public ParentGameEngine
{
public:
	SingleGame(Player player);
	~SingleGame();
private:
	void run();
	void displayInWindow(sf::RenderWindow & window);
	void moveDownAllActiveBlocks();
	bool placeNewTetromino();
	int getLineToClear();
	bool checkForInactiveBlock();
	void checkPlayersMove(sf::RenderWindow & window);
	Player player;
};

