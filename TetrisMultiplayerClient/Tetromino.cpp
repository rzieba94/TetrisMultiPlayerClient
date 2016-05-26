#include "stdafx.h"
#include "Tetromino.h"

Tetromino::Tetromino(sf::Vector2i & position, const sf::Color * color) : TetrisShape(position)
{
	this->color = color;
}

Tetromino::~Tetromino()
{
}

void Tetromino::rotate()
{
	for (std::shared_ptr<Brick> brick : bricksList)
	{
		int newX = position.x + position.y - brick->getPosition().y - Brick::BRICK_SIZE;
		int newY = brick->getPosition().x + position.y - position.x;
		brick->setPosition(sf::Vector2i(newX, newY));
	}
}

void Tetromino::moveRight()
{
	position.x += Brick::BRICK_SIZE;
	for (std::shared_ptr<Brick> brick : bricksList)
	{
		brick->move(sf::Vector2i(Brick::BRICK_SIZE, 0));
	}
}

void Tetromino::moveLeft()
{
	position.x -= Brick::BRICK_SIZE;
	for (std::shared_ptr<Brick> brick : bricksList)
	{
		brick->move(sf::Vector2i(-Brick::BRICK_SIZE, 0));
	}
}

void Tetromino::moveDown()
{
	position.y += Brick::BRICK_SIZE;
	for (std::shared_ptr<Brick> brick : bricksList)
	{
		brick->move(sf::Vector2i(0, Brick::BRICK_SIZE));
	}
}

void Tetromino::drop(int rowsCount)
{
	position.y += Brick::BRICK_SIZE * rowsCount;
	for (std::shared_ptr<Brick> brick : bricksList)
	{
		brick->move(sf::Vector2i(0, Brick::BRICK_SIZE * rowsCount));
	}
}

bool Tetromino::checkColision(TetrisShape & tetrisShape, MoveType & moveType)
{
	return false;
}

std::list<sf::RectangleShape> Tetromino::getDrawableItems()
{
	std::list<sf::RectangleShape> drawableItems;
	for (std::shared_ptr<Brick> brick : bricksList)
	{
		drawableItems.push_back(brick->getDrawable());
	}
	return drawableItems;
}

void Tetromino::clearLine(int lineNumber)
{

}
