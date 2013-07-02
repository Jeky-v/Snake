#include "GlobalVariables.h"

#include "GameClassic.h"
#include "ModuleName.h"
#include "ModuleMgr.h"

#include "CellSnake.h"
#include "CellEmpty.h"
#include "CellEat.h"
#include "CellWallUndestructable.h"

void GameClassic::doInit()
{
	if(full_screen_mode)
	{
		cell_pic[0]=IMG_Load("Pictures/Game/CellPic/cellsnake.1.21.png");
		cell_pic[1]=IMG_Load("Pictures/Game/CellPic/.png");
		cell_pic[2]=IMG_Load("Pictures/Game/CellPic/cellempty.21.png");
		cell_pic[3]=IMG_Load("Pictures/Game/CellPic/celleat.21.png");
		cell_pic[4]=IMG_Load("Pictures/Game/CellPic/cellwalldestructable.21.png");
		cell_pic[5]=IMG_Load("Pictures/Game/CellPic/cellwallundestructable.21.png");
		cell_pic[6]=IMG_Load("Pictures/Game/CellPic/cellreverse.21.png");
		cell_pic[7]=IMG_Load("Pictures/Game/CellPic/cellteleport.21.png");
		cell_pic[8]=IMG_Load("Pictures/Game/CellPic/celleatgenerator.21.png");
		topPicture=IMG_Load("Pictures/Game/TopPictures/toppicture0.1366.png");
	}
	else
	{
		cell_pic[0]=IMG_Load("Pictures/Game/CellPic/cellsnake.1.14.png");
		cell_pic[1]=IMG_Load("Pictures/Game/CellPic/.png");
		cell_pic[2]=IMG_Load("Pictures/Game/CellPic/cellempty.14.png");
		cell_pic[3]=IMG_Load("Pictures/Game/CellPic/celleat.14.png");
		cell_pic[4]=IMG_Load("Pictures/Game/CellPic/cellwalldestructable.14.png");
		cell_pic[5]=IMG_Load("Pictures/Game/CellPic/cellwallundestructable.14.png");
		cell_pic[6]=IMG_Load("Pictures/Game/CellPic/cellreverse.14.png");	
		cell_pic[7]=IMG_Load("Pictures/Game/CellPic/cellteleport.14.png");
		cell_pic[8]=IMG_Load("Pictures/Game/CellPic/celleatgenerator.14.png");
		topPicture=IMG_Load("Pictures/Game/TopPictures/toppicture0.900.png");
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

	for(int i=0;i<65;i++)
	{
		Converter.CreateConvert<CellWallUndestructable>(i,0);
		Converter.CreateConvert<CellWallUndestructable>(i,34);
	}
	for(int j=0;j<35;j++)
	{
		Converter.CreateConvert<CellWallUndestructable>(0,j);
		Converter.CreateConvert<CellWallUndestructable>(64,j);
	}
	Converter.CreateConvert<CellEat>(5,5);
	Converter.Convert();
}

bool GameClassic::doRun()
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
		DrawTop();
		SDL_Delay(50);
	}
	else
	{
		Converter.Convert();
		DrawField();
		DrawTop();
		GameOver();		
	}
	return true;
}

void GameClassic::doClose()
{
	
	for (int i=0;i<65;i++)
	{
		for(int j=0;j<35;j++)
		{
			delete global_map[i][j];
		}
	}
	for(int i=0;i<9;i++)
	{
		SDL_FreeSurface(cell_pic[i]);
		cell_pic[i]=NULL;
	}
	SDL_FreeSurface(topPicture);
}

void GameClassic::GameOver()
{
	m_mgr->SetActiveModule(MAINMENU);
	delete snake;
}

void GameClassic::DrawTop()
{
	int score=snake->GetScore();
	char text[10];
	sprintf(text, "%d", score);
	text[9]='/0';
	
	SDL_Rect src,des;
	src.x=0;
	src.y=0;
	src.h=topPicture->h;
	src.w=topPicture->w;
	des=src;
	
	SDL_BlitSurface(topPicture,&src,screen,&des);
	
	DrawText(5,5,"Score:",20,250,152,5);
	DrawText(130,5,text,20,250,152,5);
	SDL_Flip(screen);
}