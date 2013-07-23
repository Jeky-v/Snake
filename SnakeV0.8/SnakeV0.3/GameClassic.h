#pragma once
#include "gamemodule.h"
#include "Snake.h"

class Snake;
class GameClassic :public GameModule
{
private:
	Snake* snake;
	Mix_Music *backgroundMusic;
public:
	void doInit();
	bool doRun();
	void doClose();
	void GameOver();
	void DrawTop();
};

