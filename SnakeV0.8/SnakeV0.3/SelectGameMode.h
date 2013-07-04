#pragma once
#include "imodule.h"
#include "MenuButton.h"

class SelectGameMode :public IModule
{
private:
	MenuButton allButtons[5];
	SDL_Surface *buttonPic[5];
	SDL_Surface *background;
	MenuButton* currentButtonPointer;
public:
	void doInit();
	bool doRun();
	void doClose();
};

