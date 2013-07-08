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
#include "CellConnectionEatGenerator.h"
#include "CellEatGenerator.h"
#include "CellConnectionTeleport.h"
#include <iostream>
#include <fstream>

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
		cell_pic[7]=IMG_Load("Pictures/Game/CellPic/cellteleport.21.png");
		cell_pic[8]=IMG_Load("Pictures/Game/CellPic/celleatgenerator.21.png");
		topPicture=IMG_Load("Pictures/Game/TopPictures/toppicture0.1366.png");
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
		cell_pic[7]=IMG_Load("Pictures/Game/CellPic/cellteleport.14.png");
		cell_pic[8]=IMG_Load("Pictures/Game/CellPic/celleatgenerator.14.png");
		topPicture=IMG_Load("Pictures/Game/TopPictures/toppicture0.900.png");
	}

	ofstream out("Levels\\1.txt",ios::binary|ios::out); //Открываем файл в двоичном режиме для записи
	int snakeDirection=2;
	out.write((char*)&snakeDirection,sizeof(snakeDirection));
	int snakeCellX=45, snakeCellY=15;

	out.write((char*)&snakeCellX,sizeof(snakeCellX));
	out.write((char*)&snakeCellY,sizeof(snakeCellY));
	snakeCellX=46;
	snakeCellY=15;
	out.write((char*)&snakeCellX,sizeof(snakeCellX));
	out.write((char*)&snakeCellY,sizeof(snakeCellY));
	snakeCellX=47;
	snakeCellY=15;
	out.write((char*)&snakeCellX,sizeof(snakeCellX));
	out.write((char*)&snakeCellY,sizeof(snakeCellY));

	int lol=2;
	int typeOfCell=0;//empty
	for (int i=0;i<65;i++)
	{
		for(int j=0;j<35;j++)
		{
			if (i==64&&j==34) out.write((char*)&lol,sizeof(lol)); 
			else out.write((char*)&typeOfCell,sizeof(typeOfCell));
		}
	}
	out.close(); //Закрываем файл
	
	LoadMap();

	for (int i=0;i<65;i++)
	{
		for(int j=0;j<35;j++)
		{
			global_map[i][j]->SetDestination(cell_pic[2]->w*i,33+cell_pic[2]->w*j,cell_pic[2]->w,cell_pic[2]->w);
		}
	}
	
	//Initialize some cells
	/*
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

	Converter.CreateConvert<CellEatGenerator>(1,1);
	
	Converter.Convert();
	CellConnectionEatGenerator* generatorConnection=new CellConnectionEatGenerator;
	global_map[1][1]->setConnection(generatorConnection,1,1);
	global_map[2][2]->setConnection(generatorConnection,2,2);

	CellConnection *cellConnection=new CellConnection;
	global_map[31][15]->setConnection(cellConnection,31,15);
	global_map[3][4]->setConnection(cellConnection,3,4);
	*/
	Converter.CreateConvert<CellWallUndestructable>(16,7);
	Converter.CreateConvert<CellWallUndestructable>(17,7);
	Converter.CreateConvert<CellWallUndestructable>(18,7);
	Converter.CreateConvert<CellWallUndestructable>(19,7);
	Converter.CreateConvert<CellWallUndestructable>(20,7);
	Converter.CreateConvert<CellWallUndestructable>(21,7);
	Converter.CreateConvert<CellWallUndestructable>(22,7);
	Converter.CreateConvert<CellWallUndestructable>(23,7);
	Converter.CreateConvert<CellWallUndestructable>(24,7);

	Converter.CreateConvert<CellWallUndestructable>(16,1);
	Converter.CreateConvert<CellWallUndestructable>(17,1);
	Converter.CreateConvert<CellWallUndestructable>(18,1);
	Converter.CreateConvert<CellWallUndestructable>(19,1);
	Converter.CreateConvert<CellWallUndestructable>(20,1);
	Converter.CreateConvert<CellWallUndestructable>(21,1);
	Converter.CreateConvert<CellWallUndestructable>(22,1);
	Converter.CreateConvert<CellWallUndestructable>(23,1);
	Converter.CreateConvert<CellWallUndestructable>(24,1);

	Converter.CreateConvert<CellWallUndestructable>(16,2);
	Converter.CreateConvert<CellWallUndestructable>(16,3);
	Converter.CreateConvert<CellWallUndestructable>(16,4);
	Converter.CreateConvert<CellWallUndestructable>(16,5);
	Converter.CreateConvert<CellWallUndestructable>(16,6);
	Converter.CreateConvert<CellWallUndestructable>(24,2);
	Converter.CreateConvert<CellWallUndestructable>(24,3);
	Converter.CreateConvert<CellWallUndestructable>(24,4);
	Converter.CreateConvert<CellWallUndestructable>(24,5);
	Converter.CreateConvert<CellWallUndestructable>(24,6);

	Converter.CreateConvert<CellEat>(20,4);
	Converter.CreateConvert<CellTeleport>(17,4);

	Converter.CreateConvert<CellWallUndestructable>(13,15);
	Converter.CreateConvert<CellEat>(14,15);
	Converter.CreateConvert<CellWallUndestructable>(15,15);
	Converter.CreateConvert<CellEat>(16,15);
	Converter.CreateConvert<CellWallUndestructable>(17,15);
	Converter.CreateConvert<CellEat>(18,15);
	Converter.CreateConvert<CellWallUndestructable>(19,15);
	Converter.CreateConvert<CellEat>(20,15);
	Converter.CreateConvert<CellWallUndestructable>(21,15);
	Converter.CreateConvert<CellEat>(22,15);
	Converter.CreateConvert<CellWallUndestructable>(23,15);
	Converter.CreateConvert<CellEat>(24,15);
	Converter.CreateConvert<CellWallUndestructable>(25,15);
	Converter.CreateConvert<CellEat>(26,15);
	Converter.CreateConvert<CellWallUndestructable>(27,15);
	Converter.CreateConvert<CellEat>(28,15);
	Converter.CreateConvert<CellWallUndestructable>(29,15);

	Converter.CreateConvert<CellWallUndestructable>(4,20);
	Converter.CreateConvert<CellWallUndestructable>(4,21);
	Converter.CreateConvert<CellWallUndestructable>(4,22);
	Converter.CreateConvert<CellWallUndestructable>(4,23);
	Converter.CreateConvert<CellWallUndestructable>(4,24);
	Converter.CreateConvert<CellWallUndestructable>(4,25);
	Converter.CreateConvert<CellWallUndestructable>(4,26);
	Converter.CreateConvert<CellWallUndestructable>(4,27);

	Converter.CreateConvert<CellWallUndestructable>(6,20);
	Converter.CreateConvert<CellWallUndestructable>(6,21);
	Converter.CreateConvert<CellWallUndestructable>(6,22);
	Converter.CreateConvert<CellWallUndestructable>(6,23);
	Converter.CreateConvert<CellWallUndestructable>(6,24);
	Converter.CreateConvert<CellWallUndestructable>(6,25);
	Converter.CreateConvert<CellWallUndestructable>(6,26);
	Converter.CreateConvert<CellWallUndestructable>(6,27);
	Converter.CreateConvert<CellWallUndestructable>(5,27);

	Converter.CreateConvert<CellEat>(5,24);
	Converter.CreateConvert<CellWallDestructable>(5,23);
	Converter.CreateConvert<CellWallDestructable>(5,22);
	Converter.CreateConvert<CellWallDestructable>(5,21);
	Converter.CreateConvert<CellWallDestructable>(5,20);
	Converter.CreateConvert<CellReverse>(5,26);

	Converter.CreateConvert<CellEatGenerator>(5,25);
	
	Converter.CreateConvert<CellTeleport>(40,60);
	Converter.Convert();
	
	CellConnectionEatGenerator* generatorConnection=new CellConnectionEatGenerator;
	global_map[5][25]->setConnection(generatorConnection,5,25);
	global_map[17][6]->setConnection(generatorConnection,17,6);	
	global_map[17][2]->setConnection(generatorConnection,17,2);
	global_map[23][6]->setConnection(generatorConnection,23,6);
	global_map[23][2]->setConnection(generatorConnection,23,2);
	
	CellConnectionTeleport* teleportConnection=new CellConnectionTeleport;
	global_map[40][60]->setConnection(teleportConnection,40,60);
	global_map[17][4]->setConnection(teleportConnection,17,4);
	

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

void GameWithLevels::doClose()
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

void GameWithLevels::DrawTop()
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

void GameWithLevels::LoadMap()
{
	int snakeDirection;
	ifstream in("Levels\\level.txt",ios::binary|ios::in);
	in.read((char*)&snakeDirection,sizeof(snakeDirection));
	int snakeCellX[3];
	int snakeCellY[3];
	in.read((char*)&snakeCellX[0],sizeof(int));
	in.read((char*)&snakeCellY[0],sizeof(int));
	in.read((char*)&snakeCellX[1],sizeof(int));
	in.read((char*)&snakeCellY[1],sizeof(int));
	in.read((char*)&snakeCellX[2],sizeof(int));
	in.read((char*)&snakeCellY[2],sizeof(int));
	int typeOfCell;


	for (int i=0;i<65;i++)
	{
		for(int j=0;j<35;j++)
		{
			in.read((char*)&typeOfCell,sizeof(typeOfCell));
			cout<< typeOfCell;
			switch (typeOfCell)
			{
				case 0:{global_map[i][j]=new CellEmpty; cout<< typeOfCell; break;}
				case 2:{global_map[i][j]=new CellReverse; cout<< typeOfCell; break;}
				case 5:{global_map[i][j]=new CellWallUndestructable; cout<< typeOfCell; break;} 
				default: {cout << "Weird type of cell, program has been stoped."; exit(4);}
			}
		}
	}

	int numberOfConnections;
	int cellsInConnection;
	in.read((char*)&numberOfConnections,sizeof(numberOfConnections));
	if (numberOfConnections)
	{
		CellConnection* connection=new CellConnection;
		connections.push_back(connection);
		in.read((char*)&cellsInConnection,sizeof(cellsInConnection));
		int cellX,cellY;
		for (int i=0;i<cellsInConnection;i++) 
		{
			in.read((char*)&cellX,sizeof(cellX));
			in.read((char*)&cellY,sizeof(cellY));
			global_map[cellX][cellY]->setConnection(connection,cellX,cellY);
		}
	}
	in.close();

	snake=new Snake(static_cast<dir_type>(snakeDirection),"snake",CellStruct(snakeCellX[0],snakeCellY[0]),CellStruct(snakeCellX[1],snakeCellY[1]),CellStruct(snakeCellX[2],snakeCellY[2]));
}