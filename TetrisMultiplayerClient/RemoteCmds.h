#pragma once
#include "stdafx.h"

struct ClientHelloMsg
{
	string cmd;
	string nick;
};

struct ConnectionStatusMsg
{
	string cmd;
	string status;
};

struct MoveMsg
{
	string cmd; //move
	string moveType; //down, left, right, drop
	string userId; // nick
	int dropCount; // 0 lub wartosc
};

struct StartGame
{
	string cmd; // startGame
	string gameType; // single, cooperation
};

struct ClearLine
{
	string cmd; //clearLine
	int lineNumber; //numerLinii
};

struct PlaceTetromino
{
	string cmd; // placeTetromino
	string tetrominoType; //typ tetromino
	int positionX;
	int positionY;
};

struct EndGame
{
	string cmd; // endGame
};