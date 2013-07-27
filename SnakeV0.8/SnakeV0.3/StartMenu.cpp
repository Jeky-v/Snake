#include "GlobalVariables.h"

#include "StartMenu.h"
#include "ModuleName.h"
#include "ModuleMgr.h"

void StartMenu::doInit()
{
	buttonPic[0]=IMG_Load("Pictures/Menu/Buttons/newgame.png");
	buttonPic[1]=IMG_Load("Pictures/Menu/Buttons/settings.png");
	buttonPic[2]=IMG_Load("Pictures/Menu/Buttons/score.png");
	buttonPic[3]=IMG_Load("Pictures/Menu/Buttons/credits.png");
	buttonPic[4]=IMG_Load("Pictures/Menu/Buttons/exit.png");
	
	if(full_screen_mode)
	{ background=IMG_Load("Pictures/Menu/Backgrounds/background0.1366.png"); }
	else
	{ background=IMG_Load("Pictures/Menu/Backgrounds/background0.900.png"); }
	
	
	SDL_Rect src,des;
	src.x=0;
	src.y=0;
	src.h=background->h;
	src.w=background->w;
	des=src;
	
	SDL_BlitSurface(background,&src,screen,&des);
	
	buttonsManager = new ButtonsManager(getModuleMgr());  
	UIElement** buttons=new UIElement* [5];  //Manager will free all of these pointers, don't afraid.
	for(int i=0;i<5;i++)
	{
	    buttons[i]=new UIElement(buttonsManager); 
		buttons[i]->setPicture(buttonPic[i]);
		if(full_screen_mode)
		{
			buttons[i]->setDestination((RESX-400)/2,55+55*i+80*i,80,400);
		}
		else
		{
			buttons[i]->setDestination((RESX-400)/2,20+20*i+80*i,80,400);
		}
		buttonsManager->addButton(buttons[i]);
	}
	buttons[0]->doScenario=[=](){m_mgr->SetActiveModule(SELECTGAMEMODE);};
	buttons[1]->doScenario=[=](){m_mgr->SetActiveModule(SETTINGS);};
	buttons[2]->doScenario=[=](){m_mgr->SetActiveModule(HELLOSCREEN);};
	buttons[3]->doScenario=[=](){};
	buttons[4]->doScenario=[=](){exit(0);}; //Must be replaced by pushing in sdl event queue SDL_QUIT event.
}

bool StartMenu::doRun()
{
	return buttonsManager->doRun();
	
}

void StartMenu::doClose()
{
	for (int i=0;i<5;i++)
	{
		SDL_FreeSurface(buttonPic[i]);
	}
	SDL_FreeSurface(background);
	delete buttonsManager;
}


