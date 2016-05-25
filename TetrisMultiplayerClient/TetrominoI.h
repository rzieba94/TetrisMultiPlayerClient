#pragma once
#include "Tetromino.h"

class TetrominoI : public Tetromino
{
public:
	TetrominoI(sf::Vector2i & position, const sf::Color * color);
	~TetrominoI();
};

