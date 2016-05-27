#pragma once
#include <SFML\Graphics\Color.hpp>
#include <SFML\System\Vector2.hpp>
#include "Tetromino.h"
#include "TetrominoType.h"
#include "TetrominoI.h"
#include "TetrominoJ.h"
#include "TetrominoL.h"
#include "TetrominoO.h"
#include "TetrominoS.h"
#include "TetrominoT.h"
#include "TetrominoZ.h"
#include <memory>
#include <random>

using namespace std;

class TetrominoFactory
{
public:
	TetrominoFactory();
	~TetrominoFactory();
	shared_ptr<Tetromino> getRandomTetromino(sf::Vector2i & position);
	shared_ptr<Tetromino> getRandomTetromino(sf::Vector2i & position, const sf::Color * color);
	shared_ptr<Tetromino> getTetromino(sf::Vector2i & position, const TetrominoType tetrominoType);
	shared_ptr<Tetromino> getTetromino(sf::Vector2i & position, const sf::Color * color, const TetrominoType tetrominoType);
private:
	const sf::Color * getRandomColor();
	const TetrominoType getRandomTetrominoType();

	default_random_engine randomGenerator;
	uniform_int_distribution<int> distribution;
};

