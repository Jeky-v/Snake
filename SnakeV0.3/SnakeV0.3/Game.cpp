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
			map[i][j]=new CellEmpty;
			map[i][j]=dynamic_cast<CellEmpty*> (map[i][j]);
			map[i][j]->SetPicture(cell_pic[2]);//cell_pic[2]->w*i,12+cell_pic[2]->w*j,cell_pic[2]->w,cell_pic[2]->w);
		}
	}
	//testting
	CellTypeConverter Converter;
	Converter.CreateConvert <CellSnake> (map[5][5]);
	Converter.Convert();
	//map[5][5]->SetPicture(cell_pic[0]);
	
	printf("%s\n",typeid(*map[5][5]).name());

	
	
	for (int i=0;i<65;i++)
	{
		for(int j=0;j<35;j++)
		{
			map[i][j]->SetDestination(cell_pic[2]->w*i,33+cell_pic[2]->w*j,cell_pic[2]->w,cell_pic[2]->w);
		}
	}
	snake1=new Snake(this,Right,"snake1",CellStruct(7,3),CellStruct(6,3),CellStruct(5,3));
	snake1->Move();
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
				break;
			}
		}

	}
	DrawField();
	SDL_Delay(100);
	return true;
}

void Game::doClose()
{
	for (int i=0;i<65;i++)
	{
		for(int j=0;j<35;j++)
		{
			delete map[i][j];
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
			if(map[i][j]!=NULL)
			{
				map[i][j]->DrawCell();
			}
		}
	}
	SDL_Flip(screen);
}