#include "stdafx.h"
#include "Brick.h"


Brick::Brick(sf::Vector2i & position, const sf::Color * color) : color(color)
{
	this->position = position;
}

Brick::Brick(int positionX, int positionY, const sf::Color * color) : position(positionX, positionY), color(color)
{
}

Brick::~Brick()
{
}

void Brick::move(sf::Vector2i & moveVector)
{
	this->position.x += moveVector.x;
	this->position.y += moveVector.y;
}

sf::RectangleShape Brick::getDrawable()
{
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(BRICK_SIZE, BRICK_SIZE));
	rectangle.setPosition(sf::Vector2f(position.x, position.y));
	rectangle.setFillColor(*color);
	rectangle.setOutlineThickness(1);
	rectangle.setOutlineColor(sf::Color(128, 128, 128, 255));
	return rectangle;
}

const sf::Vector2i Brick::getPosition()const
{
	return position;
}

void Brick::setPosition(sf::Vector2i & newPosition)
{
	this->position = newPosition;
}