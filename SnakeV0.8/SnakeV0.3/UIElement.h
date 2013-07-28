#pragma once
#include "ButtonsManager.h"
#include "ModuleMgr.h"
#include <functional> 
#include <SDL.h>
using std::tr1::function;

class ButtonsManager;
class ModuleManager;
class UIElement
{
public:
	UIElement(ButtonsManager* buttonsManager,function <void()> scenario=0,SDL_Surface* picture=NULL, int x=0,int y=0,int h=0,int w=0);
	
    virtual	bool processEvents();
	bool checkCollision(int x, int y);
	void setManager(ButtonsManager* ptr){managerPointer=ptr;}
	void setPicture(SDL_Surface* newSurface);
	void setDestination(int x,int y, int h, int w);
	void drawButton();
	
	function <void()> doScenario;
	bool isActive;
private:
	ModuleMgr* m_mgr;
	ButtonsManager* managerPointer;
	SDL_Surface *buttonPicture;
	SDL_Rect source;
	SDL_Rect destination;
	
};

