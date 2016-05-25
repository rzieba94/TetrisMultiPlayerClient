#pragma once
#include "Tetromino.h"

class TetrominoS : public Tetromino
{
public:
	TetrominoS(sf::Vector2i & position, const sf::Color * color);
	~TetrominoS();
};

