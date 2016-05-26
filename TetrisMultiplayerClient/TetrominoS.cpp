#include "stdafx.h"
#include "TetrominoS.h"


TetrominoS::TetrominoS(sf::Vector2i & position, const sf::Color * color) : Tetromino(position, color)
{
	bricksList.push_front(std::shared_ptr<Brick>(new Brick(position.x - Brick::BRICK_SIZE, position.y - Brick::BRICK_SIZE, color)));
	bricksList.push_front(std::shared_ptr<Brick>(new Brick(position.x, position.y - Brick::BRICK_SIZE, color)));
	bricksList.push_front(std::shared_ptr<Brick>(new Brick(position.x - (Brick::BRICK_SIZE * 2), position.y, color)));
	bricksList.push_front(std::shared_ptr<Brick>(new Brick(position.x - Brick::BRICK_SIZE, position.y, color)));
}


TetrominoS::~TetrominoS()
{
}
