#pragma once
#include <SFML\Graphics\Color.hpp>
#include <SFML\System\Vector2.hpp>
#include "Tetromino.h"
#include "TetrominoType.h"
#include <random>

class TetrominoFactory
{
public:
	TetrominoFactory();
	~TetrominoFactory();
	Tetromino * getRandomTetromino(sf::Vector2i & position);
	Tetromino * getRandomTetromino(sf::Vector2i & position, const sf::Color * color);
	Tetromino * getTetromino(sf::Vector2i & position, const TetrominoType & tetrominoType);
	Tetromino * getTetromino(sf::Vector2i & position, const sf::Color * color, const TetrominoType & tetrominoType);
private:
	const sf::Color * getRandomColor();
	const TetrominoType & getRandomTetrominoType();

	std::default_random_engine randomGenerator;
	std::uniform_int_distribution<int> distribution;
};

