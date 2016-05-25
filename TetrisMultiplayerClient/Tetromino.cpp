#include "stdafx.h"
#include "Tetromino.h"


Tetromino::Tetromino(sf::Vector2i * position, const sf::Color * color) : TetrisShape(position)
{
	this->color = color;
}


Tetromino::~Tetromino()
{
}

bool Tetromino::rotate()
{
	return false;
}

bool Tetromino::moveRight()
{
	return false;
}

bool Tetromino::moveLeft()
{
	return false;
}

bool Tetromino::moveDown() 
{
	return false;
}

bool Tetromino::drop(int rowsCount)
{
	return false;
}

bool Tetromino::checkColision(TetrisShape * tetrisShape, MoveType moveType)
{
	return false;
}

void Tetromino::getDrawableItems()
{
}

void Tetromino::clearLine(int lineNumber)
{

}
