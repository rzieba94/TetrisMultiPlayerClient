#include "stdafx.h"
#include "TetrominoFactory.h"

TetrominoFactory::TetrominoFactory() : distribution(0, 6)
{
}


TetrominoFactory::~TetrominoFactory()
{
}

shared_ptr<Tetromino> TetrominoFactory::getTetromino(sf::Vector2i & position, const sf::Color * color, const TetrominoType tetrominoType)
{
	switch (tetrominoType)
	{
	default:
	case TetrominoTypeI:
		return shared_ptr<Tetromino>(new TetrominoI(position, color));
	case TetrominoTypeJ:
		return shared_ptr<Tetromino>(new TetrominoJ(position, color));
	case TetrominoTypeL:
		return shared_ptr<Tetromino>(new TetrominoL(position, color));
	case TetrominoTypeO:
		return shared_ptr<Tetromino> (new TetrominoO(position, color));
	case TetrominoTypeS:
		return shared_ptr<Tetromino>(new TetrominoS(position, color));
	case TetrominoTypeT:
		return shared_ptr<Tetromino>(new TetrominoT(position, color));
	case TetrominoTypeZ:
		return shared_ptr<Tetromino>(new TetrominoZ(position, color));
	}
}

shared_ptr<Tetromino> TetrominoFactory::getTetromino(sf::Vector2i & position, const TetrominoType tetrominoType)
{
	return getTetromino(position, getRandomColor(), tetrominoType);
}

shared_ptr<Tetromino> TetrominoFactory::getRandomTetromino(sf::Vector2i & position, const sf::Color * color)
{
	return getTetromino(position, color, getRandomTetrominoType());
}

shared_ptr<Tetromino> TetrominoFactory::getRandomTetromino(sf::Vector2i & position)
{
	return getRandomTetromino(position, getRandomColor());
}

const sf::Color * TetrominoFactory::getRandomColor()
{
	switch (distribution(randomGenerator))
	{
	default:
	case 0:
		return &sf::Color::Blue;
	case 1:
		return &sf::Color::Cyan;
	case 2:
		return &sf::Color::Green;
	case 3:
		return &sf::Color::Magenta;
	case 4:
		return &sf::Color::Red;
	case 5:
		return &sf::Color::Yellow;
	case 6:
		return &sf::Color::White;
	}
}

const TetrominoType TetrominoFactory::getRandomTetrominoType()
{
	switch (distribution(randomGenerator))
	{
	default:
	case 0:
		return TetrominoTypeI;
	case 1:
		return TetrominoTypeJ;
	case 2:
		return TetrominoTypeL;
	case 3:
		return TetrominoTypeO;
	case 4:
		return TetrominoTypeS;
	case 5:
		return TetrominoTypeT;
	case 6:
		return TetrominoTypeZ;
	}
}