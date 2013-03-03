#pragma once
#include <list>

#include "CellStruct.h"

using namespace std;

enum dir_type {Up,Down,Left,Right};

class Snake
{
private:
	dir_type direction;
	SDL_Surface *picture;
	char name[20];
	int score;
	list <CellStruct> snake_list; 
public:
	Snake();
	Snake(dir_type start_direction,char *text,CellStruct cell1,CellStruct cell2,CellStruct cell3);
	~Snake(void);

	void Move();
	void SetDirection(dir_type new_direction);
	dir_type GetDirection();
};

