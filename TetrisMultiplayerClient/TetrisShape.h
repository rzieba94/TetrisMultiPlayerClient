#pragma once
#include "MoveType.h"
#include <SFML/System/Vector2.hpp>

class TetrisShape
{
public:
	TetrisShape(sf::Vector2i & position);
	~TetrisShape();
	virtual bool rotate() = 0;
	virtual bool moveRight() = 0;
	virtual bool moveLeft() = 0;
	virtual bool moveDown() = 0;
	virtual bool drop(int rowsCount) = 0;
	virtual bool checkColision(TetrisShape & tetrisShape, MoveType & moveType) = 0;
	virtual void getDrawableItems() = 0;
	virtual void clearLine(int lineNumber) = 0;
protected:
	sf::Vector2i position;
};

