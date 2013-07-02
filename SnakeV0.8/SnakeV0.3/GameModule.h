#pragma once
#include "imodule.h"
#include <SDL.h>

class GameModule :public IModule
{
protected:
	SDL_Surface* topPicture;
public:
	void DrawField();
	void Pause();
	void DrawText(int x, int y, char *inputtext, int size, int R, int G, int B);
	
	void virtual GameOver()=0;
	void virtual DrawTop()=0;
};

