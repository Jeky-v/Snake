#pragma once
#include "GlobalVariables.h"

class Snake;
class Cell
{
private:
	SDL_Rect dest;
	SDL_Surface *picture;
	bool activity;
public:
	void SetDestination(int x,int y,int h, int w);
	int GetX();
	int GetY();
	int GetH();
	int GetW();
	void SetActivity(bool newact);
	bool GetActivity();
	void SetPicture(SDL_Surface *new_pic);
	SDL_Surface *GetPicture();
	void DrawCell();
	virtual void Interaction(Snake &snake,int x,int y)=0;
};

