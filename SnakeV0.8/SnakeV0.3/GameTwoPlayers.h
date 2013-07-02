#pragma once
#include "gamemodule.h"
#include "Snake.h"

class GameTwoPlayers :public GameModule
{
private:
	int player1Score;
	int player2Score;

	Snake* snake1;
	Snake* snake2;
public:
	Snake* GetFirstSnake();
	Snake* GetSecondSnake();
	void doInit();
	bool doRun();
	void doClose();
	void GameOver();
	void DrawTop();
};

