#pragma once
#include "GameModule.h"
#include "Snake.h"
#include "CellConnection.h"
class Snake;
class CellConnection;
class GameWithLevels :public GameModule
{
private:
	int score;
	int current_map_number;
	Snake *snake;
	std::list<CellConnection*> connections;
public:

	void doInit();
	bool doRun();
	void doClose();
	
	void LoadMap();
	void GameOver();

	friend class Snake;
};

