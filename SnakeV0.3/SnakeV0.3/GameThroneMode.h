#pragma once
#include "gamemodule.h"
class GameThroneMode :public GameModule
{
public:
	void doInit();
	bool doRun();
	void doClose();
	void GameOver();
};

