#include "UIElement.h"
#include "GlobalVariables.h"
#include "ModuleName.h"
UIElement::UIElement(ButtonsManager* buttonsManager,function <void()> scenario,SDL_Surface* picture,int _x, int _y, int _h, int _w)
{
	managerPointer=buttonsManager;
	m_mgr=managerPointer->m_mgr;
	setDestination(_x,_y,_h,_w);
	doScenario=scenario;
	if (picture) setPicture(picture);
	isActive=false;

	source.x=0;
	source.y=0;
	source.h=80;
	source.w=400;
	destination.x=0;
	destination.y=0;
	destination.h=80;
	destination.w=400;
}


bool UIElement::processEvents()
{
	SDL_Event event;
	SDL_WaitEvent(&event);
	
	switch(event.type)
	{
		case SDL_QUIT:
		{
			return false;
			break;
		}	
		case SDL_KEYDOWN:
		{
			if ( event.key.keysym.sym == SDLK_ESCAPE ) 
			{
				m_mgr->SetActiveModule(MAINMENU);	
				return true;
			} 
			
			if ( event.key.keysym.sym == SDLK_DOWN)
			{ 
				managerPointer->goDown();
			}
			if ( event.key.keysym.sym == SDLK_UP)
			{ 
				managerPointer->goUp();
			}
			if (event.key.keysym.sym == SDLK_RETURN)
			{
				doScenario();
			}
			break;
		}
		case SDL_MOUSEMOTION:
		{
		    managerPointer->findButton(event.motion.x,event.motion.y);
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			if(event.button.button == SDL_BUTTON_LEFT)
			{
				(*managerPointer->findButton(event.motion.x, event.motion.y))->doScenario();
			}
			break;
		}
	}

	return true;

}

void UIElement::setPicture(SDL_Surface* newSurface)
{
	buttonPicture=newSurface;
}
void UIElement::setDestination(int x,int y, int h, int w)
{
	destination.x=x;
	destination.y=y;
	destination.h=h;
	destination.w=w;
}

bool UIElement::checkCollision(int x, int y)
{
	if(x>=destination.x && x<=destination.x+destination.w && y>=destination.y && y<=destination.y+destination.h) return true;
	else return false;
}

void UIElement::drawButton()
{
	if(isActive)
	{source.y=source.h;}
	else
	{source.y=0;}
	SDL_BlitSurface(buttonPicture,&source,screen,&destination);
}