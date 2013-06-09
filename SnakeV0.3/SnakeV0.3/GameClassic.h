#pragma once
#include "gamemodule.h"
class GameClassic :public GameModule
{
public:
	void doInit();
	bool doRun();
	void doClose();
	void GameOver();
};

