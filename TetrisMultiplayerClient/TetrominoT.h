#pragma once
#include "Tetromino.h"

class TetrominoT : public Tetromino
{
public:
	TetrominoT(sf::Vector2i & position, const sf::Color * color);
	~TetrominoT();
};

