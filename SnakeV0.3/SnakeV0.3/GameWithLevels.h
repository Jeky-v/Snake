#pragma once
#include "GameModule.h"
#include "Cell.h"
#include "Snake.h"
#include "CellConnection.h"
class Snake;
class CellConnection;
class GameWithLevels :public GameModule
{
private:
	int score;
	int current_map_number;
	std::list<CellConnection*> connections;
	Snake *snake;
public:

	void doInit();
	bool doRun();
	void doClose();
	
	void LoadMap();
	void GameOver();

	friend class Snake;
};

