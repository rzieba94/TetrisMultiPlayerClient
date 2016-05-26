#pragma once
#include "MoveType.h"
#include <SFML/System/Vector2.hpp>
#include <list>
#include <SFML/Graphics.hpp>

class TetrisShape
{
public:
	TetrisShape(sf::Vector2i & position);
	virtual ~TetrisShape();
	virtual void rotate() = 0;
	virtual void moveRight() = 0;
	virtual void moveLeft() = 0;
	virtual void moveDown() = 0;
	virtual void drop(int rowsCount) = 0;
	virtual bool checkColision(TetrisShape & tetrisShape, MoveType & moveType) = 0;
	virtual std::list<sf::RectangleShape> getDrawableItems() = 0;
	virtual void clearLine(int lineNumber) = 0;
protected:
	sf::Vector2i position;
};

