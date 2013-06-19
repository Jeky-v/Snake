#include"Cell.h"
#include "CellConection.h"
void Cell::SetDestination(int x,int y,int h, int w)
{
	dest.x=x;
	dest.y=y;
	dest.h=h;
	dest.w=w;
}

int Cell::GetX()
{
	return dest.x;
}

int Cell::GetY()
{
	return dest.y;
}

int Cell::GetH()
{
	return dest.h;
}

int Cell::GetW()
{
	return dest.w;
}

void Cell::SetActivity(bool newact)
{
	activity=newact;
}

bool Cell::GetActivity()
{
	return activity;
}

void Cell::SetPicture(SDL_Surface *new_pic)
{
	picture=new_pic;
}

void Cell::DrawCell()
{
	SDL_Rect sour;

	sour.h=dest.h;
	sour.w=dest.w;

	if(activity)
	{
		sour.x=0;
		sour.y=0;
	}
	else
	{
		sour.x=0;
		sour.y=sour.h;
	}
	SDL_BlitSurface(picture,&sour,screen,&dest);
}

SDL_Surface* Cell::GetPicture()
{
	return picture;
}
void Cell::setConnection(CellConection* someConnection)
{
	connection=someConnection;
	connection->addCell(this);

}

