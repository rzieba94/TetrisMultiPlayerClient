#pragma once
#include "TetrisShape.h"
#include <SFML/Graphics/Color.hpp>

class Tetromino : TetrisShape
{
public:
	virtual ~Tetromino();
	bool rotate();
	bool moveRight();
	bool moveLeft();
	bool moveDown();
	bool drop(int rowsCount);
	bool checkColision(TetrisShape * tetrisShape, MoveType moveType);
	void getDrawableItems();
	void clearLine(int lineNumber);
protected:
	Tetromino(sf::Vector2i * position, const sf::Color * color);
	const sf::Color * color;
};

