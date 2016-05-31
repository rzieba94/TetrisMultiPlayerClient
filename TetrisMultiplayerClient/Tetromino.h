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
	list<sf::RectangleShape> getDrawableItems();
	void clearLine(int lineNumber);
	list<shared_ptr<Brick>> getBricksList();
	bool isEmptyBricksList();
protected:
	Tetromino(sf::Vector2i & position, const sf::Color * color);
	const sf::Color * color;
	list<shared_ptr<Brick>> bricksList;
};

