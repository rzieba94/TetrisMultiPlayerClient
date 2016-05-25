#pragma once
#include "Tetromino.h"

class TetrominoJ : public Tetromino
{
public:
	TetrominoJ(sf::Vector2i & position, const sf::Color * color);
	~TetrominoJ();
};

