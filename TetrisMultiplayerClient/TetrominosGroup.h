#pragma once
#include "TetrisShape.h"

class TetrominosGroup : public TetrisShape
{
public:
	TetrominosGroup(sf::Vector2i & position);
	~TetrominosGroup();
};

