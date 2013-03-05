#pragma once
#include "imodule.h"
#include "Cell.h"
#include "Snake.h"

class Game :public IModule
{
private:
	int score;
	int current_map_number;
	Cell *map[65][35];

	Snake *snake1;
	Snake *snake2;
public:

	void doInit();
	bool doRun();
	void doClose();
	
	void LoadMap();
	void Pause();
	void DrawField();
	void DrawCell();

	friend class Snake;
};

