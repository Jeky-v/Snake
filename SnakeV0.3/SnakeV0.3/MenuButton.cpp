#include "GlobalVariables.h"
#include "MenuButton.h"

MenuButton::MenuButton()
{
	button_pic=NULL;
	state=false;//non active
	source.x=0;
	source.y=0;
	source.h=80;
	source.w=400;
	destination.x=0;
	destination.y=0;
	destination.h=80;
	destination.w=400;
}
MenuButton::MenuButton(int h,int w)
{
	button_pic=NULL;
	state=false;//non active
	source.x=0;
	source.y=0;
	source.h=h;
	source.w=w;
	destination.x=0;
	destination.y=0;
	destination.h=h;
	destination.w=w;
}
MenuButton::~MenuButton(void)
{

}
//===========================================================
void MenuButton::SetButtonPic(SDL_Surface* new_surface)
{
	button_pic=new_surface;
}

void MenuButton::SetDestination(int x,int y, int h, int w)
{
	destination.x=x;
	destination.y=y;
	destination.h=h;
	destination.w=w;
}

bool MenuButton::GetState()
{
	return state;
}
//=========================================================
void MenuButton::CheckActivity(int x,int y)
{
	if(x>=destination.x && x<=destination.x+destination.w && y>=destination.y && y<=destination.y+destination.h)
	{
		state=true;
	}
	else
	{
		state=false;
	}
}

void MenuButton::DrawButton()
{
	if(state)
	{source.y=source.h;}
	else
	{source.y=0;}
	SDL_BlitSurface(button_pic,&source,screen,&destination);
	SDL_Flip(screen);
}