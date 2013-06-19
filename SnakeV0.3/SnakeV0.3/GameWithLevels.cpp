#include "GlobalVariables.h"

#include "GameWithLevels.h"
#include "ModuleName.h"
#include "ModuleMgr.h"

#include "CellTypeConverter.h"
#include "CellSnake.h"
#include "CellEmpty.h"
#include "CellEat.h"
#include "CellWallDestructable.h"
#include "CellWallUndestructable.h"
#include "CellReverse.h"
#include "CellConnection.h"
#include "CellTeleport.h"
void GameWithLevels::doInit()
{
	if(full_screen_mode)
	{
		cell_pic[0]=IMG_Load("Pictures/Game/CellPic/cellsnake.1.21.png");
		//cell_pic[1]=IMG_Load("Pictures/Game/CellPic/.png");
		cell_pic[2]=IMG_Load("Pictures/Game/CellPic/cellempty.21.png");
		cell_pic[3]=IMG_Load("Pictures/Game/CellPic/celleat.21.png");
		cell_pic[4]=IMG_Load("Pictures/Game/CellPic/cellwalldestructable.21.png");
		cell_pic[5]=IMG_Load("Pictures/Game/CellPic/cellwallundestructable.21.png");
		cell_pic[6]=IMG_Load("Pictures/Game/CellPic/cellreverse.21.png");
	}
	else
	{
		cell_pic[0]=IMG_Load("Pictures/Game/CellPic/cellsnake.1.14.png");
		//cell_pic[1]=IMG_Load("Pictures/Game/CellPic/.png");
		cell_pic[2]=IMG_Load("Pictures/Game/CellPic/cellempty.14.png");
		cell_pic[3]=IMG_Load("Pictures/Game/CellPic/celleat.14.png");
		cell_pic[4]=IMG_Load("Pictures/Game/CellPic/cellwalldestructable.14.png");
		cell_pic[5]=IMG_Load("Pictures/Game/CellPic/cellwallundestructable.14.png");
		cell_pic[6]=IMG_Load("Pictures/Game/CellPic/cellreverse.14.png");	
	}
		
	for (int i=0;i<65;i++)
	{
		for(int j=0;j<35;j++)
		{
			global_map[i][j]=new CellEmpty;
			global_map[i][j]=dynamic_cast<CellEmpty*> (global_map[i][j]);
		}
	}
	
	for (int i=0;i<65;i++)
	{
		for(int j=0;j<35;j++)
		{
			global_map[i][j]->SetDestination(cell_pic[2]->w*i,33+cell_pic[2]->w*j,cell_pic[2]->w,cell_pic[2]->w);
		}
	}
	snake=new Snake(Left,"snake",CellStruct(45,15),CellStruct(46,15),CellStruct(47,15));
	
	//Initialize some cells
	Converter.CreateConvert<CellEat>(20,20);
	Converter.CreateConvert<CellEat>(25,20);
	Converter.CreateConvert<CellEat>(30,20);
	Converter.CreateConvert<CellEat>(20,25);
	Converter.CreateConvert<CellEat>(25,25);
	Converter.CreateConvert<CellEat>(30,25);
	Converter.CreateConvert<CellEat>(20,30);
	Converter.CreateConvert<CellEat>(25,30);
	Converter.CreateConvert<CellEat>(30,30);

	Converter.CreateConvert<CellReverse>(20,10);
	Converter.CreateConvert<CellReverse>(25,10);
	Converter.CreateConvert<CellReverse>(30,10);

	Converter.CreateConvert<CellWallDestructable>(20,15);
	Converter.CreateConvert<CellWallDestructable>(21,15);
	Converter.CreateConvert<CellWallDestructable>(22,15);
	Converter.CreateConvert<CellWallDestructable>(23,15);
	Converter.CreateConvert<CellWallDestructable>(24,15);
	Converter.CreateConvert<CellWallDestructable>(25,15);
	Converter.CreateConvert<CellWallDestructable>(26,15);
	Converter.CreateConvert<CellWallDestructable>(27,15);
	Converter.CreateConvert<CellWallDestructable>(28,15);
	Converter.CreateConvert<CellWallDestructable>(29,15);
	Converter.CreateConvert<CellWallDestructable>(30,15);

	Converter.CreateConvert<CellTeleport>(31,15);
	Converter.CreateConvert<CellTeleport>(3,4);
	Converter.Convert();
	CellConnection *cellConnection=new CellConnection;
	global_map[31][15]->setConnection(cellConnection,31,15);
	global_map[3][4]->setConnection(cellConnection,3,4);
	
	// end initialize

}

bool GameWithLevels::doRun()
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
	if(snake->Move())
	{
		Converter.Convert();
		DrawField();
		SDL_Delay(50);
	}
	else
	{
		Converter.Convert();
		DrawField();		
		GameOver();
	}
	connections.push_back(0);
	return true;
}

void GameWithLevels::doClose()
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

void GameWithLevels::LoadMap()
{
	snake=new Snake(Left,"snake",CellStruct(45,15),CellStruct(46,15),CellStruct(47,15));
}

void GameWithLevels::GameOver()
{
	if(snake->GetDead())
	{
		m_mgr->SetActiveModule(MAINMENU);
		//DrawText(RESX/2-230,RESY/2-60,"You are LOOOOOOOSER",40,255,0,0);
	}
	else
	{
		//DrawText(RESX/2-230,RESY/2-60,"Win",60,255,0,0);
		current_map_number++;
		m_mgr->SetActiveModule(MAINMENU);
	}
	delete snake;
	//LoadMap();
}
