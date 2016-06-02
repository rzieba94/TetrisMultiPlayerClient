#pragma once
#include "ParentGameEngine.h"

class CooperationGame : public ParentGameEngine
{
public:
	CooperationGame(shared_ptr<LocalPlayer> ownerPlayer, vector<string> otherPlayersNicknames);
	~CooperationGame();
	void placeNewTetromino(sf::Vector2i pos, TetrominoType type, string playerNick);
	void forwardMoveCommand(MoveMsg msg);
	void run();
};

