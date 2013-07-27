#pragma once
#include "imodule.h"
#include "MenuButton.h"
#include "ButtonsManager.h"
class SelectGameMode :public IModule
{
private:
	SDL_Surface *buttonPic[5];
	SDL_Surface *background;
	MenuButton* currentButtonPointer;
	ButtonsManager* buttonsManager;
public:
	SelectGameMode():IModule(),buttonsManager(0){}
	void doInit();
	bool doRun();
	void doClose();
};

