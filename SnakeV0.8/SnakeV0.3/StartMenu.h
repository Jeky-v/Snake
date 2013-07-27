#pragma once
#include "imodule.h"
#include <string>
#include "MenuButton.h"
#include "ButtonsManager.h"
class ButtonsManager;
class StartMenu :
	public IModule
{
private:
	MenuButton AllButtons[6];
	ButtonsManager* buttonsManager;
	SDL_Surface *buttonPic[6];
	SDL_Surface *background;
	MenuButton* currentButtonPointer;
public:
	void doInit();
	bool doRun();
	void doClose();
};

