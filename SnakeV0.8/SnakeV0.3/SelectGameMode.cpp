#include "GlobalVariables.h"

#include "SelectGameMode.h"
#include "ModuleName.h"
#include "ModuleMgr.h"

void SelectGameMode::doInit()
{

	buttonPic[0]=IMG_Load("Pictures/Menu/Buttons/levels.png");
	buttonPic[1]=IMG_Load("Pictures/Menu/Buttons/twoplayers.png");
	buttonPic[2]=IMG_Load("Pictures/Menu/Buttons/classicgame.png");
	buttonPic[3]=IMG_Load("Pictures/Menu/Buttons/thronemode.png");
	buttonPic[4]=IMG_Load("Pictures/Menu/Buttons/back.png");
	
	
	

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
	buttons[0]->doScenario=[=](){m_mgr->SetActiveModule(GAMEWITHLEVELS);};
	buttons[1]->doScenario=[=](){m_mgr->SetActiveModule(TWOPLAYERS);};
	buttons[2]->doScenario=[=](){m_mgr->SetActiveModule(CLASSIC);};
	buttons[3]->doScenario=[=](){m_mgr->SetActiveModule(THRONEMODE);};
	buttons[4]->doScenario=[=](){m_mgr->SetActiveModule(MAINMENU);};
}

bool SelectGameMode::doRun()
{
	return buttonsManager->doRun();
}

void SelectGameMode::doClose()
{
	for (int i=0;i<5;i++)
	{
		SDL_FreeSurface(buttonPic[i]);
	}
	SDL_FreeSurface(background);
	delete buttonsManager;
}

