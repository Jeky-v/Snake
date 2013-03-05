#pragma once
#include <list>
#include "CellStruct.h"
#include "Game.h"

class Game;
enum dir_type {Up,Down,Left,Right};

class Snake
{
private:
	Game *game_pointer;
	dir_type direction;
	SDL_Surface *picture;
	char name[20];
	int score;
	std::list <CellStruct> snake_list; 
public:
	Snake();
	Snake(Game *new_game_pointer,dir_type start_direction,char *text,CellStruct cell1,CellStruct cell2,CellStruct cell3);
	~Snake(void);

	void Move();
	void SetDirection(dir_type new_direction);
	dir_type GetDirection();
};

