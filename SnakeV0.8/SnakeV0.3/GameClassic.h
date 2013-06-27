#pragma once
#include "gamemodule.h"
#include "Snake.h"

class Snake;
class GameClassic :public GameModule
{
private:
	int score;

	Snake* snake;
public:
	void doInit();
	bool doRun();
	void doClose();
	void GameOver();

	friend class Snake;
};

