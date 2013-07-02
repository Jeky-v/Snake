#pragma once
#include "imodule.h"
#include <string>
#include "MenuButton.h"

class StartMenu :
	public IModule
{
private:
	MenuButton AllButtons[6];
	SDL_Surface *ButtonPic[6];
	SDL_Surface *background;
	MenuButton* currentButtonPointer;
public:
	void doInit();
	bool doRun();
	void doClose();
};

