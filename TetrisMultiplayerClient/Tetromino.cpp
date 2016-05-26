#include "stdafx.h"
#include "Tetromino.h"
#include <iostream>

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

int Tetromino::getDropCount(TetrisShape & tetrisShape, int boardWidth)
{
	list<shared_ptr<Brick>> otherBricksList = tetrisShape.getBricksList();
	
	list<sf::Vector2i> brickPositions;
	for (shared_ptr<Brick> brick : bricksList)
	{
		brickPositions.push_back(brick->getPosition());
	}
	
	int dropCounter;
	for (dropCounter = 0; dropCounter < 20; dropCounter++)
	{
		list<sf::Vector2i>::iterator it;

		for (it = brickPositions.begin(); it != brickPositions.end(); ++it)
		{
			it->y += Brick::BRICK_SIZE;
			if (checkColision(*it, boardWidth, otherBricksList))
			{
				return dropCounter;
			}
		}
	}

	return dropCounter;
}

bool Tetromino::checkColision(TetrisShape & tetrisShape, MoveType moveType, int boardWidth)
{
	cout << "w check colision1";
	sf::Vector2i moveVector;
	list<shared_ptr<Brick>> otherBricksList = tetrisShape.getBricksList();
	cout << "w check colision2";
	switch (moveType)
	{
	case DOWN:
		moveVector = sf::Vector2i(0, Brick::BRICK_SIZE);
		break;
	case LEFT:
		moveVector = sf::Vector2i(-Brick::BRICK_SIZE, 0);
		break;
	case RIGHT:
		moveVector = sf::Vector2i(Brick::BRICK_SIZE, 0);
		break;
	}
	cout << "w check colision3";
	for (shared_ptr<Brick> brick : bricksList)
	{
		cout << "w check colision4";
		sf::Vector2i currentBrickPosition = brick->getPosition();
		cout << "w check colision5";
		if (moveType == ROTATE)
		{
			int newX = position.x + position.y - brick->getPosition().y - Brick::BRICK_SIZE;
			int newY = brick->getPosition().x + position.y - position.x;
			currentBrickPosition = sf::Vector2i(newX, newY);
		}
		else
		{
			currentBrickPosition.x += moveVector.x;
			currentBrickPosition.y += moveVector.y;
		}
		cout << "w check colision6";
		if (checkColision(currentBrickPosition, boardWidth, otherBricksList))
		{
			return true;
		}
	}
	return false;
}

bool Tetromino::checkColision(sf::Vector2i currentBrickPosition, int boardWidth, list<shared_ptr<Brick>> otherBricksList)
{
	if (currentBrickPosition.x < 0 || currentBrickPosition.x >= boardWidth || currentBrickPosition.y >= 400) // TODO: wysokosc planszy powinna byc stala, nie zahardcodowana
	{
		return true;
	}
	if (!otherBricksList.empty())
	{
		for (shared_ptr<Brick> otherBrick : otherBricksList)
		{
			sf::Vector2i otherBrickPosition = otherBrick->getPosition();
			if (currentBrickPosition.x == otherBrickPosition.x && currentBrickPosition.y == otherBrickPosition.y)
			{
				return true;
			}
		}
	}
	return false;
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