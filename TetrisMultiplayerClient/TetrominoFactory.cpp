#include "stdafx.h"
#include "TetrominoFactory.h"
#include "TetrominoI.h"
#include "TetrominoJ.h"
#include "TetrominoL.h"
#include "TetrominoO.h"
#include "TetrominoS.h"
#include "TetrominoT.h"
#include "TetrominoZ.h"


TetrominoFactory::TetrominoFactory() : distribution(0, 6)
{
}


TetrominoFactory::~TetrominoFactory()
{
}

Tetromino * TetrominoFactory::getTetromino(sf::Vector2i & position, const sf::Color * color, const TetrominoType & tetrominoType)
{
	switch (tetrominoType)
	{
	case TetrominoTypeI:
		return new TetrominoI(position, color);
	case TetrominoTypeJ:
		return new TetrominoJ(position, color);
	case TetrominoTypeL:
		return new TetrominoL(position, color);
	case TetrominoTypeO:
		return new TetrominoO(position, color);
	case TetrominoTypeS:
		return new TetrominoS(position, color);
	case TetrominoTypeT:
		return new TetrominoT(position, color);
	case TetrominoTypeZ:
		return new TetrominoZ(position, color);
	}
}

Tetromino * TetrominoFactory::getTetromino(sf::Vector2i & position, const TetrominoType & tetrominoType)
{
	return getTetromino(position, getRandomColor(), tetrominoType);
}

Tetromino * TetrominoFactory::getRandomTetromino(sf::Vector2i & position, const sf::Color * color)
{
	return getTetromino(position, color, getRandomTetrominoType());
}

Tetromino * TetrominoFactory::getRandomTetromino(sf::Vector2i & position)
{
	return getRandomTetromino(position, getRandomColor());
}

const sf::Color * TetrominoFactory::getRandomColor()
{
	switch (distribution(randomGenerator))
	{
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

const TetrominoType & TetrominoFactory::getRandomTetrominoType()
{
	switch (distribution(randomGenerator))
	{
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