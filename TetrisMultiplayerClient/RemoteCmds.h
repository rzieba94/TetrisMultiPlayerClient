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

// gracz wysyla chec ruchu, serwer odsyla potwierdzenie gdy ruch jest ok
struct MoveMsg
{
	string cmd; //move
	string moveType; //down, left, right, drop
	string userId; // nick
	int dropCount; // 0 lub wartosc
};

//gracz wysyla info aby serwer utworzyl watek gry, gdy gra sie rozpocznie (sa wszyscy uzytkownicy) serwer odsyla info o rozpoczeciu gry
struct StartGame
{
	string cmd; // startGame
	string gameType; // single, cooperation
	int playersNumber; // liczba graczy na ktorych oczekuje
	list<string> userIds; // lista id graczy
};

//serwer wysyla info o tym ktora linia ma byc wyczyszczona
struct ClearLine
{
	string cmd; //clearLine
	int lineNumber; //numer linii
};

//serwer wysyla info gdzie umiescic tetromino, jakie i dla ktorego gracza
struct PlaceTetromino
{
	string cmd; // placeTetromino
	string tetrominoType; //typ tetromino
	string userId; // nick
	int positionX;
	int positionY;
};

//serwer wysyla: endGame, endServer, timeout(gdy czas oczekiwania na graczy przekroczony) klient wysy³a: getGamesList
struct SimpleCommand
{
	string cmd;
};

//serwer wysyla informacje o przyznaniu punktow
struct AddScore
{
	string cmd; //addScore
	int score;
};

//serwer wysyla po otrzymaniu zapytania od gracza
struct GamesList
{
	string cmd; //gamesList
	list<int> gamesIds; // id gier oczekujacych na graczy
	list<string> gameType; //typy gier oczekujacych na graczy
};

//klient wysyla aby polaczyc sie do istniejacej gry
struct ConnectToGame
{
	string cmd; //connectToGame
	int gameId; //id gry
};