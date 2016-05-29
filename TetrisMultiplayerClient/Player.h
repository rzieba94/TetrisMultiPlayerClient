#pragma once
#include <string>
#include <memory>
#include "Tetromino.h"

using namespace std;

class Player
{
public:
	Player(string nick);
	~Player();
	void addScore(int score);
	const int getScore();
	const string getNick();
	void setActiveTetromino(shared_ptr<Tetromino> activeTetromino);
	shared_ptr<Tetromino> getActiveTetromino();
	sf::Vector2i getStartPosition();
	void getStartPosition(int startPosition);
private:
	string nick;
	int score;
	shared_ptr<Tetromino> activeTetromino;
	sf::Vector2i startPosition;
};

