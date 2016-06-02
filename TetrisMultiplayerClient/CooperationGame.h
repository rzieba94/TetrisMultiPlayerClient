#pragma once
#include "ParentGameEngine.h"
#include "LocalPlayer.h"
#include "RemoteCmds.h"

class CooperationGame : public ParentGameEngine
{
public:
	CooperationGame(shared_ptr<LocalPlayer> ownerPlayer, vector<string> otherPlayersNicknames);
	~CooperationGame();
	void placeNewTetromino(sf::Vector2i pos, TetrominoType type, string playerNick);
	void forwardMoveCommand(MoveMsg msg);
	void clearLine(int lineNumber);
	void endGameCloseWindow();
	void run();
private:
	void displayInWindow(sf::RenderWindow & window);
	void moveDownAllActiveBlocks();
	void checkPlayersMove(sf::RenderWindow & window);
	shared_ptr<LocalPlayer> ownerPlayer;
	list<Player> otherPlayers;
	bool firstBrick;
	bool closeWindow;
	int numOfPlayers = 0;
};

