#pragma once
#include "gamemodule.h"
class GameTwoPlayers :public GameModule
{
public:
	void doInit();
	bool doRun();
	void doClose();
	void GameOver();
};

