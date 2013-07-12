#include "GlobalVariables.h"

#include "GameTwoPlayers.h"
#include "ModuleName.h"
#include "ModuleMgr.h"

#include "CellTypeConverter.h"
#include "CellSnake.h"
#include "CellEmpty.h"
#include "CellEat.h"

void GameTwoPlayers::doInit()
{
	if(full_screen_mode)
	{
		cell_pic[0]=IMG_Load("Pictures/Game/CellPic/cellsnake.1.21.png");
		cell_pic[1]=IMG_Load("Pictures/Game/CellPic/cellsnake.2.21.png");
		cell_pic[2]=IMG_Load("Pictures/Game/CellPic/cellempty.21.png");
		cell_pic[3]=IMG_Load("Pictures/Game/CellPic/celleat.21.png");
		topPicture=IMG_Load("Pictures/Game/TopPictures/toppicture0.1366.png");
	}
	else
	{
		cell_pic[0]=IMG_Load("Pictures/Game/CellPic/cellsnake.1.14.png");
		cell_pic[1]=IMG_Load("Pictures/Game/CellPic/cellsnake.2.14.png");
		cell_pic[2]=IMG_Load("Pictures/Game/CellPic/cellempty.14.png");
		cell_pic[3]=IMG_Load("Pictures/Game/CellPic/celleat.14.png");
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
	Converter.CreateConvert <CellEat> (32,18);
	Converter.Convert();
	snake1=new Snake(Left,"Snake1",CellStruct(61,17),CellStruct(62,17),CellStruct(63,17));
	snake2=new Snake(Right,"Snake2",CellStruct(3,18),CellStruct(2,18),CellStruct(1,18),1);	
	player1Score=0;
	player2Score=0;
}

bool GameTwoPlayers::doRun()
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
				if ( event.key.keysym.sym == SDLK_p || event.key.keysym.sym == SDLK_SPACE) 
				{
					doPause();
				} 
				if ( event.key.keysym.sym == SDLK_UP && snake1->GetDirection()!=Down) 
				{
					snake1->SetDirection(Up);
				} 
				if ( event.key.keysym.sym == SDLK_w && snake2->GetDirection()!=Down) 
				{
					snake2->SetDirection(Up);
				} 
				if ( event.key.keysym.sym == SDLK_DOWN && snake1->GetDirection()!=Up) 
				{
					snake1->SetDirection(Down);
				} 
				if ( event.key.keysym.sym == SDLK_s && snake2->GetDirection()!=Up) 
				{
					snake2->SetDirection(Down);
				} 
				if ( event.key.keysym.sym == SDLK_LEFT && snake1->GetDirection()!=Right) 
				{
					snake1->SetDirection(Left);
				} 
				if ( event.key.keysym.sym == SDLK_a && snake2->GetDirection()!=Right) 
				{
					snake2->SetDirection(Left);
				} 
				if ( event.key.keysym.sym == SDLK_RIGHT && snake1->GetDirection()!=Left) 
				{
					snake1->SetDirection(Right);
				} 
				if ( event.key.keysym.sym == SDLK_d && snake2->GetDirection()!=Left) 
				{
					snake2->SetDirection(Right);
				} 
				break;
			}
		}
	}
	if(snake1->Move()&&snake2->Move())
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

void GameTwoPlayers::doClose()
{
	delete snake1;
	delete snake2;
	for (int i=0;i<65;i++)
	{
		for(int j=0;j<35;j++)
		{
			delete global_map[i][j];
		}
	}
	for(int i=0;i<4;i++)
	{
		SDL_FreeSurface(cell_pic[i]);
		cell_pic[i]=NULL;
	}
	SDL_FreeSurface(topPicture);
}

void GameTwoPlayers::GameOver()
{	
	int middleX=(int) RESX/2;
	int middleY=(int) RESY/2;
	if(snake1->GetDead())
	{
		player2Score++;
		DrawText(middleX-250,middleY-10,"Player  WASD  WIN",40,250,152,5);
	}
	if(snake2->GetDead())
	{
		player1Score++;
		DrawText(middleX-250,middleY-10,"Player  ULDR  WIN",40,250,152,5);
	}
	SDL_Flip(screen);
	SDL_Delay(1500);
	
	for (int i=0;i<65;i++)
	{
		for(int j=0;j<35;j++)
		{
			Converter.CreateConvert<CellEmpty>(i,j);
		}
	}
	Converter.Convert();
	Converter.CreateConvert <CellEat> (32,18);
	Converter.Convert();

	delete snake1;
	delete snake2;
	snake1=new Snake(Left,"Snake1",CellStruct(61,17),CellStruct(62,17),CellStruct(63,17));
	snake2=new Snake(Right,"Snake2",CellStruct(3,18),CellStruct(2,18),CellStruct(1,18),1);	

	SDL_PumpEvents();
	SDL_Event event[30];
	SDL_PeepEvents(event,30,SDL_GETEVENT,SDL_KEYDOWNMASK);
}

void GameTwoPlayers::DrawTop()
{
	char player1MainScore[5];
	char player2MainScore[5];
	char player1SnakeLength[5];
	char player2SnakeLength[5];

	int player1SnakeScore=snake1->GetScore();
	int player2SnakeScore=snake2->GetScore();

	int middle=RESX/2;
	sprintf(player1MainScore,"%d",player1Score);
	sprintf(player2MainScore,"%d",player2Score);
	sprintf(player1SnakeLength,"%d",(int) player1SnakeScore/10+3);
	sprintf(player2SnakeLength,"%d",(int) player2SnakeScore/10+3);

	player1MainScore[4]='/0';
	player2MainScore[4]='/0';
	player1SnakeLength[4]='/0';
	player2SnakeLength[4]='/0';

	SDL_Rect src,des;
	src.x=0;
	src.y=0;
	src.h=topPicture->h;
	src.w=topPicture->w;
	des=src;	
	SDL_BlitSurface(topPicture,&src,screen,&des);
	
	DrawText(10,5,"Player WASD",20,255,66,116);	//Red
	DrawText(235,5,player2SnakeLength,20,255,66,116);
	DrawText(middle-60,5,player2MainScore,20,255,66,116);

	DrawText(middle-5,5," - ",20,250,152,5);	//Orange
	
	DrawText(middle+50,5,player1MainScore,20,130,232,130);	//Green
	DrawText(RESX-280,5,player1SnakeLength,20,130,232,130);
	DrawText(RESX-220,5,"Player ULDR",20,130,232,130);
	
	SDL_Flip(screen);
}

Snake* GameTwoPlayers::GetFirstSnake()
{
	return snake1;
}

Snake* GameTwoPlayers::GetSecondSnake()
{
	return snake2;
}