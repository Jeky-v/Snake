#pragma once
#include "GlobalVariables.h"

#include "IModule.h"
#include "MenuButton.h"
#include <string>

class Settings:public IModule
{
private:
	SDL_Surface *background;
	SDL_Surface *tickbox;
	SDL_Surface *box;
	SDL_Surface *backpic;
	MenuButton back;
	MenuButton tick;
public:
	Settings();
	void DrawText(int x,int y,char *text,int size,int R,int G,int B);
	void ChangeScreenMode();
	void SaveSettings();
	void doInit();
	bool doRun();
	void doClose();
};

