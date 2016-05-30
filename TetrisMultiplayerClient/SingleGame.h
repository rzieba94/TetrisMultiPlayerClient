#pragma once
#include "ParentGameEngine.h"
#include "Player.h"

using namespace std;

class SingleGame : public ParentGameEngine
{
public:
	SingleGame();
	SingleGame(Player player);
	~SingleGame();
	bool placeNewTetromino(sf::Vector2i pos,TetrominoType type);
	sf::RenderWindow *getWindow();
private:
	void run();
	void displayInWindow(sf::RenderWindow & window);
	void moveDownAllActiveBlocks();
	int getLineToClear();
	bool checkForInactiveBlock();
	void checkPlayersMove(sf::RenderWindow & window);
	Player player; 
	sf::RenderWindow *window;
	bool firstBrick;
};

