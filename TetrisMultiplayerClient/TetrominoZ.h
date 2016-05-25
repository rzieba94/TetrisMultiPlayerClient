#pragma once
#include "Tetromino.h"

class TetrominoZ : public Tetromino
{
public:
	TetrominoZ(sf::Vector2i & position, const sf::Color * color);
	~TetrominoZ();
};

