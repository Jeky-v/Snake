#include "GlobalVariables.h"

#include "StartMenu.h"
#include "ModuleName.h"
#include "ModuleMgr.h"

void StartMenu::doInit()
{
	ButtonPic[0]=IMG_Load("Pictures/Menu/Buttons/newgame.png");
	ButtonPic[1]=IMG_Load("Pictures/Menu/Buttons/settings.png");
	ButtonPic[2]=IMG_Load("Pictures/Menu/Buttons/score.png");
	ButtonPic[3]=IMG_Load("Pictures/Menu/Buttons/credits.png");
	ButtonPic[4]=IMG_Load("Pictures/Menu/Buttons/exit.png");
	
	if(full_screen_mode)
	{ background=IMG_Load("Pictures/Menu/Backgrounds/background0.1366.png"); }
	else
	{ background=IMG_Load("Pictures/Menu/Backgrounds/background0.900.png"); }
	
	for(int i=0;i<5;i++)
	{
		AllButtons[i].SetButtonPic(ButtonPic[i]);
		if(full_screen_mode)
		{
			AllButtons[i].SetDestination((RESX-400)/2,55+55*i+80*i,80,400);
		}
		else
		{
			AllButtons[i].SetDestination((RESX-400)/2,20+20*i+80*i,80,400);
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
		AllButtons[i].DrawButton();
	}
	
	SDL_Flip(screen);
}

bool StartMenu::doRun()
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
			{return false;} 
			break;
		}
		case SDL_MOUSEMOTION:
		{
			for(int i=0;i<5;i++)
			{
				AllButtons[i].CheckActivity(event.motion.x,event.motion.y);
			}
			
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			if(event.button.button == SDL_BUTTON_LEFT)
			{
				if(AllButtons[0].GetState())
				{
					m_mgr->SetActiveModule(SELECTGAMEMODE);
					return true;
				}
				if(AllButtons[1].GetState())
				{
					m_mgr->SetActiveModule(SETTINGS);
					return true;
				}
				if(AllButtons[2].GetState())
				{
				
				}
				if(AllButtons[3].GetState())
				{
					m_mgr->SetActiveModule(HELLOSCREEN);
					return true;
				}
				if(AllButtons[4].GetState())
				{
					return false;
				}
			}
			break;
		}
	}
	for(int i=0;i<5;i++)
	{
		AllButtons[i].DrawButton();
	}
	return true;
}

void StartMenu::doClose()
{
	for (int i=0;i<5;i++)
	{
		SDL_FreeSurface(ButtonPic[i]);
	}
	SDL_FreeSurface(background);
}


