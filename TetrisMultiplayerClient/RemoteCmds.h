#pragma once
#include <string>
#include "TetrominoType.h"
#include "GameType.h"

struct ClientHelloMsg
{
	int cmd;
	string nick;
};

struct ConnectionStatusMsg
{
	int cmd;
	string status;
};

// gracz wysyla chec ruchu, serwer odsyla potwierdzenie gdy ruch jest ok
struct MoveMsg
{
	int cmd; //move
	MoveType moveType; //down, left, right, drop
	string userId; // nick
	int dropCount; // 0 lub wartosc
};

//gracz wysyla info aby serwer utworzyl watek gry, gdy gra sie rozpocznie (sa wszyscy uzytkownicy) serwer odsyla info o rozpoczeciu gry
struct StartGame
{
	int cmd; // startGame
	int gameType; // single, cooperation
	int playersNumber; // liczba graczy na ktorych oczekuje
	string userIds; // lista id graczy oddzielone srednikami
};

//serwer wysyla info o tym ktora linia ma byc wyczyszczona
struct ClearLine
{
	int cmd; //clearLine
	int lineNumber; //numer linii
};

//serwer wysyla info gdzie umiescic tetromino, jakie i dla ktorego gracza
struct PlaceTetromino
{
	int cmd; // placeTetromino
	TetrominoType tetrominoType; //typ tetromino
	string userId; // nick
	int positionX;
	int positionY;
};

//serwer wysyla: endGame, endServer, timeout(gdy czas oczekiwania na graczy przekroczony) klient wysy³a: getGamesList
struct SimpleCommand
{
	int cmd;
};

//serwer wysyla informacje o przyznaniu punktow
struct AddScore
{
	int cmd; //addScore
	int score;
};

//serwer wysyla po otrzymaniu zapytania od gracza
struct GamesList
{
	int cmd; //gamesList
	list<int> gamesIds; // id gier oczekujacych na graczy
	list<GameType> gameType; //typy gier oczekujacych na graczy
};

//klient wysyla aby polaczyc sie do istniejacej gry
struct ConnectToGame
{
	int cmd; //connectToGame
	int gameId; //id gry
};

//serwer wysyla do klientow podczas oczekiwania na dolaczenie uzytkownikow
struct WaitingTime
{
	int cmd;
	int waitingtime;
};