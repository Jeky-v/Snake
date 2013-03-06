#pragma once
#include "imodule.h"
#include "Cell.h"
#include "Snake.h"

class Snake;
class Game :public IModule
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
	void Pause();
	void DrawField();
	void DrawCell();

	friend class Snake;
};

