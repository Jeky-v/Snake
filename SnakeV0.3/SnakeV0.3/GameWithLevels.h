#pragma once
#include "GameModule.h"
#include "Cell.h"
#include "Snake.h"

class Snake;
class GameWithLevels :public GameModule
{
private:
	int score;
	int current_map_number;

	Snake *snake;
public:

	void doInit();
	bool doRun();
	void doClose();
	
	void LoadMap();
	void GameOver();

	friend class Snake;
};

