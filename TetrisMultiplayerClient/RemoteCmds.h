#pragma once
#include <string>
#include "Cmds.h"
#include "TetrominoType.h"
#include "GameType.h"

struct ClientHelloMsg
{
	Cmds cmd;
	string nick;
};

struct ConnectionStatusMsg
{
	Cmds cmd;
	string status;
};

// gracz wysyla chec ruchu, serwer odsyla potwierdzenie gdy ruch jest ok
struct MoveMsg
{
	Cmds cmd; //move
	MoveType moveType; //down, left, right, drop
	string userId; // nick
	int dropCount; // 0 lub wartosc
};

//gracz wysyla info aby serwer utworzyl watek gry, gdy gra sie rozpocznie (sa wszyscy uzytkownicy) serwer odsyla info o rozpoczeciu gry
struct StartGame
{
	Cmds cmd; // startGame
	GameType gameType; // single, cooperation
	int playersNumber; // liczba graczy na ktorych oczekuje
	list<string> userIds; // lista id graczy
};

//serwer wysyla info o tym ktora linia ma byc wyczyszczona
struct ClearLine
{
	Cmds cmd; //clearLine
	int lineNumber; //numer linii
};

//serwer wysyla info gdzie umiescic tetromino, jakie i dla ktorego gracza
struct PlaceTetromino
{
	Cmds cmd; // placeTetromino
	TetrominoType tetrominoType; //typ tetromino
	string userId; // nick
	int positionX;
	int positionY;
};

//serwer wysyla: endGame, endServer, timeout(gdy czas oczekiwania na graczy przekroczony) klient wysy�a: getGamesList
struct SimpleCommand
{
	Cmds cmd;
};

//serwer wysyla informacje o przyznaniu punktow
struct AddScore
{
	Cmds cmd; //addScore
	int score;
};

//serwer wysyla po otrzymaniu zapytania od gracza
struct GamesList
{
	Cmds cmd; //gamesList
	list<int> gamesIds; // id gier oczekujacych na graczy
	list<GameType> gameType; //typy gier oczekujacych na graczy
};

//klient wysyla aby polaczyc sie do istniejacej gry
struct ConnectToGame
{
	Cmds cmd; //connectToGame
	int gameId; //id gry
};

//serwer wysyla do klientow podczas oczekiwania na dolaczenie uzytkownikow
struct WaitingTime
{
	int cmd;
	int waitingtime;
};