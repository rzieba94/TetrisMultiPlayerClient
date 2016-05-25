#pragma once
#include "Tetromino.h"

class TetrominoL : public Tetromino
{
public:
	TetrominoL(sf::Vector2i & position, const sf::Color * color);
	~TetrominoL();
};

