#include "GlobalVariables.h"
#include "Snake.h"
#include "CellTypeConverter.h"
#include "CellSnake.h"

Snake::Snake()
{
	score=0;
	dead=false;
}

Snake::Snake(dir_type start_direction,char *text,CellStruct cell1,CellStruct cell2,CellStruct cell3)
{
	direction=start_direction;
	score=0;
	dead=false;
	strncpy(name,text,19);
	snake_list.push_front(cell3);
	snake_list.push_front(cell2);
	snake_list.push_front(cell1);

	CellTypeConverter Converter;
	Converter.CreateConvert <CellSnake> (cell1.CellX,cell1.CellY);
	Converter.Convert();
	Converter.CreateConvert <CellSnake> (cell2.CellX,cell2.CellY);
	Converter.Convert();	
	Converter.CreateConvert <CellSnake> (cell3.CellX,cell3.CellY);
	Converter.Convert();	
}

Snake::~Snake(void)
{
	snake_list.clear();
}

void Snake::SetScore(int new_score)
{
	score=new_score;
}
int Snake::GetScore()
{
	return score;
}
void Snake::SetDead(bool new_dead)
{
	dead=new_dead;
}
bool Snake::GetDead()
{
	return dead;
}
bool Snake::Move()
{
	CellStruct temp;
	switch(direction)
	{
	case Up:
		{
			temp.CellX=snake_list.front().CellX;
			if(snake_list.front().CellY==0)
			{
				temp.CellY=34;//это нужно чтобы змейка выезжала с противоположной стороны
			}
			else
			{
				temp.CellY=snake_list.front().CellY-1;
			}
			break;
		}
	case Down:
		{
			temp.CellX=snake_list.front().CellX;
			if(snake_list.front().CellY==34)
			{
				temp.CellY=0;
			}
			else
			{
				temp.CellY=snake_list.front().CellY+1;
			}
			break;
		}
	case Left:
		{
			if(snake_list.front().CellX==0)
			{
				temp.CellX=64;
			}
			else
			{
				temp.CellX=snake_list.front().CellX-1;
			}
			temp.CellY=snake_list.front().CellY;
			break;
		}
	case Right:
		{
			if(snake_list.front().CellX==64)
			{
				temp.CellX=0;
			}
			else
			{
				temp.CellX=snake_list.front().CellX+1;
			}
			temp.CellY=snake_list.front().CellY;
			break;
		}

	}
	return global_map[temp.CellX][temp.CellY]->Interaction(*this,temp.CellX,temp.CellY);
}
void Snake::SetDirection(dir_type new_direction)
{
	direction=new_direction;
}
dir_type Snake::GetDirection()
{
	return direction;
}
