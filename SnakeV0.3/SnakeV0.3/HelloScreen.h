#pragma once
#include "imodule.h"
#include <string>

class HelloScreen :public IModule
{
private:
	SDL_Surface *Logo;
public:
	void doInit();
	bool doRun();
	void doClose();
	void DrawText(int x,int y,char *inputtext,int size,int R,int G,int B);
};

