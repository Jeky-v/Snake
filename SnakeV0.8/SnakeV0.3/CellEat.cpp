#include "GlobalVariables.h"

#include "ModuleName.h"
#include "GameTwoPlayers.h"

#include "CellEat.h"
#include "CellSnake.h"

class CellSnake;
int CellEat::cell_eat_counter=0;
CellEat::CellEat()
{
	SetActivity(true);
	SetPicture(cell_pic[3]);
	cell_eat_counter++;
}
bool CellEat::Interaction(Snake &snake, int x, int y)
{
	Mix_PlayChannel(-1,sounds[0],0);

	snake.SetScore(snake.GetScore()+10);
	
	snake.snake_list.push_front(CellStruct(x,y));
	Converter.CreateConvert <CellSnake> (x,y);
	Converter.Convert();
	global_map[x][y]->SetPicture(snake.GetPicture());
	cell_eat_counter--;
	if(mgr.getCurrentModuleName()==CLASSIC)
	{
		bool temp=true;
		int randomX=0;
		int randomY=0;
		while(temp)
		{
			temp=false;
			randomX=1+rand()%(63);
			randomY=1+rand()%(33);
			for(list<CellStruct>::iterator it=snake.snake_list.begin();it!=snake.snake_list.end();++it)
			{
				if(randomX==(*it).CellX&&randomY==(*it).CellY)
				{
					temp=true;
				}
			}
		}
		Converter.CreateConvert<CellEat>(randomX,randomY);
		return true;			
	}
	if(mgr.getCurrentModuleName()==TWOPLAYERS)
	{
		GameTwoPlayers* twoPlayers;
		twoPlayers=dynamic_cast<GameTwoPlayers*>(mgr.getCurrentModulePtr());
		Snake* second_snake;
		if((twoPlayers->GetFirstSnake())->GetName()==snake.GetName())
		{
			second_snake=twoPlayers->GetSecondSnake();
		}
		else
		{
			second_snake=twoPlayers->GetFirstSnake();
		}

		bool temp=true;
		int randomX=0;
		int randomY=0;
		while(temp)
		{
			temp=false;
			randomX=rand()%(64);
			randomY=rand()%(34);
			for(list<CellStruct>::iterator it=snake.snake_list.begin();it!=snake.snake_list.end();++it)
			{
				if(randomX==(*it).CellX&&randomY==(*it).CellY)
				{
					temp=true;
				}
			}
			for(list<CellStruct>::iterator it=second_snake->snake_list.begin();it!=second_snake->snake_list.end();++it)
			{
				if(randomX==(*it).CellX&&randomY==(*it).CellY)
				{
					temp=true;
				}
			}
		}
		Converter.CreateConvert<CellEat>(randomX,randomY);
		return true;		
	}
	if(mgr.getCurrentModuleName()==GAMEWITHLEVELS)
	{
		if(cell_eat_counter==0)
		{		
			return false;
		}
		
	}
	return true;
}