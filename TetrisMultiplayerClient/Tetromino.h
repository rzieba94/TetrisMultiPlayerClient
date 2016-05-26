#pragma once
#include "TetrisShape.h"
#include "Brick.h"
#include <list>
#include <memory>
#include <SFML/Graphics/Color.hpp>

class Tetromino : public TetrisShape
{
public:
	virtual ~Tetromino();
	void rotate();
	void moveRight();
	void moveLeft();
	void moveDown();
	void drop(int rowsCount);
	bool checkColision(TetrisShape & tetrisShape, MoveType & moveType);
	std::list<sf::RectangleShape> getDrawableItems();
	void clearLine(int lineNumber);
protected:
	Tetromino(sf::Vector2i & position, const sf::Color * color);
	const sf::Color * color;
	std::list<std::shared_ptr<Brick>> bricksList;
};

