#include "CellEat.h"
#include "CellSnake.h"
#include "GlobalVariables.h"
#include "ModuleName.h"

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
	//if (mgr.getCurrentModuleName()==std::string(GAMEWITHLEVELS))   
	
	snake.snake_list.push_front(CellStruct(x,y));
	snake.SetScore(snake.GetScore()+10);
	Converter.CreateConvert <CellSnake> (x,y);
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
	if(mgr.getCurrentModuleName()==GAMEWITHLEVELS)
	{
		if(cell_eat_counter==0)
		{		
			return false;
		}
		else
		{
			return true;
		}
	}
}