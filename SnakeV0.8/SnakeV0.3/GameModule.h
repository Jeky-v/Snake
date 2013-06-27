#pragma once
#include "imodule.h"
class GameModule :public IModule
{
public:
	void DrawField();
	void Pause();
	void DrawText(int x, int y, char *inputtext, int size, int R, int G, int B);
	
	void virtual GameOver()=0;
};

