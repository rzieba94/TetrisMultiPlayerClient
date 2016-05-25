#pragma once
#include "Tetromino.h"

class TetrominoO : public Tetromino
{
public:
	TetrominoO(sf::Vector2i & position, const sf::Color * color);
	~TetrominoO();
};

