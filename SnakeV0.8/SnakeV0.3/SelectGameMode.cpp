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
	
	for(int i=0;i<5;i++)
	{
		allButtons[i].SetButtonPic(buttonPic[i]);
		if(full_screen_mode)
		{
			allButtons[i].SetDestination((RESX-400)/2,55+55*i+80*i,80,400);
		}
		else
		{
			allButtons[i].SetDestination((RESX-400)/2,20+20*i+80*i,80,400);
		}	
	}
	SDL_Rect src,des;
	src.x=0;
	src.y=0;
	src.h=background->h;
	src.w=background->w;
	des=src;
	
	SDL_BlitSurface(background,&src,screen,&des);
	
	for(int i=0;i<5;i++)
	{
		allButtons[i].DrawButton();
	}	
	SDL_Flip(screen);
}

bool SelectGameMode::doRun()
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
			break;
		}
		case SDL_MOUSEMOTION:
		{
			for(int i=0;i<5;i++)
			{
				allButtons[i].CheckActivity(event.motion.x,event.motion.y);
			}
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			if(event.button.button == SDL_BUTTON_LEFT)
			{
				if(allButtons[0].GetState())
				{
					m_mgr->SetActiveModule(GAMEWITHLEVELS);
					return true;
				}
				if(allButtons[1].GetState())
				{
					m_mgr->SetActiveModule(TWOPLAYERS);
					return true;
				}
				if(allButtons[2].GetState())
				{
					m_mgr->SetActiveModule(CLASSIC);
					return true;
				}
				if(allButtons[3].GetState())
				{
					m_mgr->SetActiveModule(THRONEMODE);
					return true;
				}
				if(allButtons[4].GetState())
				{
					m_mgr->SetActiveModule(MAINMENU);
					return true;
				}
			}
			break;
		}
	}
	for(int i=0;i<5;i++)
	{
		allButtons[i].DrawButton();
	}
	return true;
}

void SelectGameMode::doClose()
{
	for (int i=0;i<5;i++)
	{
		SDL_FreeSurface(buttonPic[i]);
	}
	SDL_FreeSurface(background);
}

