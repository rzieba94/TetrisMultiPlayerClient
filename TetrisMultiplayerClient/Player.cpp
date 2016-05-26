#include "stdafx.h"
#include "Player.h"


Player::Player(string nick, int startPosition) : nick(nick)
{
	this->startPosition = sf::Vector2i(startPosition * 5 * Brick::BRICK_SIZE, 20);
	this->score = 0;
}


Player::~Player()
{
}

void Player::addScore(int score)
{
	this->score += score;
}

const int Player::getScore()
{
	return score;
}

const string Player::getNick()
{
	return nick;
}

void Player::setActiveTetromino(shared_ptr<Tetromino> activeTetromino)
{
	this->activeTetromino = activeTetromino;
}

shared_ptr<Tetromino> Player::getActiveTetromino()
{
	return activeTetromino;
}

sf::Vector2i Player::getStartPosition()
{
	return startPosition;
}