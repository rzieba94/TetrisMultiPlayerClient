#pragma once
#include "TetrisShape.h"

class TetrominosGroup : public TetrisShape
{
public:
	TetrominosGroup(sf::Vector2i & position);
	~TetrominosGroup();
	list<sf::RectangleShape> getDrawableItems();
	void clearLine(int lineNumber);
	list<shared_ptr<Brick>> getBricksList();
	void addTetrisShape(shared_ptr<TetrisShape> tetrisShape);
	bool isEmptyBricksList();
	void deleteUnusedShapes();
private:
	void deleteTetrisShape(shared_ptr<TetrisShape> shapeToDelete);

	list<shared_ptr<TetrisShape>> tetrisShapesList;
};

