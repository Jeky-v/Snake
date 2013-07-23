#pragma once
#include "gamemodule.h"
#include "Snake.h"

class GameThroneMode :public GameModule
{
private:
	int player1Score;
	int player2Score;
	Mix_Music* backgroundMusic;

	Snake* snake1;
	Snake* snake2;
public:
	void doInit();
	bool doRun();
	void doClose();
	void GameOver();
	void DrawTop();
};

