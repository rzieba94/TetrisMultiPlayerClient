#pragma once
#include "ParentGameEngine.h"
#include "LocalPlayer.h"

using namespace std;

class SingleGame : public ParentGameEngine
{
public:
	SingleGame(shared_ptr<LocalPlayer> player);
	~SingleGame();
	void placeNewTetromino(sf::Vector2i pos,TetrominoType type);
	void endGameCloseWindow();
	void run();
private:
	void displayInWindow(sf::RenderWindow & window);
	void moveDownAllActiveBlocks();
	void checkPlayersMove(sf::RenderWindow & window);
	shared_ptr<LocalPlayer> player;
	bool firstBrick;
	bool closeWindow;
};

