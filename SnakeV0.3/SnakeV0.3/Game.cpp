#include "GlobalVariables.h"

#include "Game.h"
#include "ModuleName.h"
#include "ModuleMgr.h"

#include "CellTypeConverter.h"
#include "CellSnake.h"
#include "CellEmpty.h"

#include <typeinfo>

void Game::doInit()
{
	if(full_screen_mode)
	{
		cell_pic[0]=IMG_Load("Pictures/Game/CellPic/cellsnake.1.21.png");
		//cell_pic[1]=IMG_Load("Pictures/Game/CellPic/.png");
		cell_pic[2]=IMG_Load("Pictures/Game/CellPic/cellempty.21.png");
		//cell_pic[3]=IMG_Load("Pictures/Game/CellPic/.png");
		//cell_pic[4]=IMG_Load("Pictures/Game/CellPic/.png");
		//cell_pic[5]=IMG_Load("Pictures/Game/CellPic/.png");
	}
	else
	{
		cell_pic[0]=IMG_Load("Pictures/Game/CellPic/cellsnake.1.14.png");
		//cell_pic[1]=IMG_Load("Pictures/Game/CellPic/.png");
		cell_pic[2]=IMG_Load("Pictures/Game/CellPic/cellempty.14.png");
		//cell_pic[3]=IMG_Load("Pictures/Game/CellPic/.png");
		//cell_pic[4]=IMG_Load("Pictures/Game/CellPic/.png");
		//cell_pic[5]=IMG_Load("Pictures/Geme/CellPic/.png");
	}
		
	for (int i=0;i<65;i++)
	{
		for(int j=0;j<35;j++)
		{
			global_map[i][j]=new CellEmpty;
			global_map[i][j]=dynamic_cast<CellEmpty*> (global_map[i][j]);
			global_map[i][j]->SetPicture(cell_pic[2]);//cell_pic[2]->w*i,12+cell_pic[2]->w*j,cell_pic[2]->w,cell_pic[2]->w);
		}
	}
	
	for (int i=0;i<65;i++)
	{
		for(int j=0;j<35;j++)
		{
			global_map[i][j]->SetDestination(cell_pic[2]->w*i,33+cell_pic[2]->w*j,cell_pic[2]->w,cell_pic[2]->w);
		}
	}
	snake=new Snake(Right,"snake",CellStruct(7,3),CellStruct(6,3),CellStruct(5,3));
}

bool Game::doRun()
{
	SDL_Event event;
	if(SDL_PollEvent(&event))
	{
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
				if ( event.key.keysym.sym == SDLK_UP && snake->GetDirection()!=Down) 
				{
					snake->SetDirection(Up);
				} 
				if ( event.key.keysym.sym == SDLK_DOWN && snake->GetDirection()!=Up) 
				{
					snake->SetDirection(Down);
				} 
				if ( event.key.keysym.sym == SDLK_LEFT && snake->GetDirection()!=Right) 
				{
					snake->SetDirection(Left);
				} 
				if ( event.key.keysym.sym == SDLK_RIGHT && snake->GetDirection()!=Left) 
				{
					snake->SetDirection(Right);
				} 
				break;
			}
		}

	}
	printf("");
	snake->Move();
	Converter.Convert();
	DrawField();
	SDL_Delay(150);
	return true;
}

void Game::doClose()
{
	for (int i=0;i<65;i++)
	{
		for(int j=0;j<35;j++)
		{
			delete global_map[i][j];
		}
	}
	for(int i=0;i<8;i++)
	{
		SDL_FreeSurface(cell_pic[i]);
	}
}

void Game::LoadMap()
{
}

void Game::Pause()
{
}

void Game::DrawField()
{
	for (int i=0;i<65;i++)
	{
		for(int j=0;j<35;j++)
		{
			if(global_map[i][j]!=NULL)
			{
				global_map[i][j]->DrawCell();
			}
		}
	}
	SDL_Flip(screen);
}