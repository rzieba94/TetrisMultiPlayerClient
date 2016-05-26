#pragma once
#include "MoveType.h"
#include <SFML/System/Vector2.hpp>
#include <list>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Brick.h"

using namespace std;

class TetrisShape
{
public:
	TetrisShape(sf::Vector2i & position);
	virtual ~TetrisShape();
	virtual list<sf::RectangleShape> getDrawableItems() = 0;
	virtual void clearLine(int lineNumber) = 0;
	virtual list<shared_ptr<Brick>> getBricksList() = 0;
	virtual bool isEmptyBricksList() = 0;
protected:
	sf::Vector2i position;
};

