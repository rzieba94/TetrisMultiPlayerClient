#pragma once
#include "SFML\System\Vector2.hpp"
class Brick
{
public:
	Brick(sf::Vector2i & position);
	~Brick();
	void move(sf::Vector2i & moveVector);
	sf::Vector2i getPosition();

	static const int BRICK_SIZE = 10;
private: 
	sf::Vector2i position;
};

