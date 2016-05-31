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
	for (shared_ptr<Brick> brick : bricksList)
	{
		int newX = position.x + position.y - brick->getPosition().y - Brick::BRICK_SIZE;
		int newY = brick->getPosition().x + position.y - position.x;
		brick->setPosition(sf::Vector2i(newX, newY));
	}
}

void Tetromino::moveRight()
{
	position.x += Brick::BRICK_SIZE;
	for (shared_ptr<Brick> brick : bricksList)
	{
		brick->move(sf::Vector2i(Brick::BRICK_SIZE, 0));
	}
}

void Tetromino::moveLeft()
{
	position.x -= Brick::BRICK_SIZE;
	for (shared_ptr<Brick> brick : bricksList)
	{
		brick->move(sf::Vector2i(-Brick::BRICK_SIZE, 0));
	}
}

void Tetromino::moveDown()
{
	position.y += Brick::BRICK_SIZE;
	for (shared_ptr<Brick> brick : bricksList)
	{
		brick->move(sf::Vector2i(0, Brick::BRICK_SIZE));
	}
}

void Tetromino::drop(int rowsCount)
{
	for (shared_ptr<Brick> brick : bricksList)
	{
		brick->move(sf::Vector2i(0, Brick::BRICK_SIZE * rowsCount));
	}
}

list<sf::RectangleShape> Tetromino::getDrawableItems()
{
	list<sf::RectangleShape> drawableItems;
	for (shared_ptr<Brick> brick : bricksList)
	{
		drawableItems.push_back(brick->getDrawable());
	}
	return drawableItems;
}

void Tetromino::clearLine(int lineNumber)
{
	if (lineNumber != -1)
	{
		list<shared_ptr<Brick>>::iterator it = bricksList.begin();
		while (it != bricksList.end())
		{
			int brickPositionY = (*it)->getPosition().y;
			int clearedLine = lineNumber * Brick::BRICK_SIZE;
			if (brickPositionY == clearedLine)
			{
				it = bricksList.erase(it);
			}
			else
			{
				if (brickPositionY < clearedLine)
				{
					(*it)->move(sf::Vector2i(0, Brick::BRICK_SIZE));
				}
				it++;
			}
		}
	}
}

list<shared_ptr<Brick>> Tetromino::getBricksList()
{
	return bricksList;
}

bool Tetromino::isEmptyBricksList()
{
	return getBricksList().empty();
}