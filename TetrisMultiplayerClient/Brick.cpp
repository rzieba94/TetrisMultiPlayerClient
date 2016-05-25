#include "stdafx.h"
#include "Brick.h"


Brick::Brick(sf::Vector2i & position)
{
	this->position = position;
}


Brick::~Brick()
{
}

void Brick::move(sf::Vector2i & moveVector)
{
	int newXValue = position.x + moveVector.x;
	int newYValue = position.y + moveVector.y;
	position.x = newXValue;
	position.y = newYValue;
}

sf::Vector2i Brick::getPosition()
{
	return position;
}