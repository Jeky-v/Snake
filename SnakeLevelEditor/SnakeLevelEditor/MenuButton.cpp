#include "MenuButton.h"

MenuButton::MenuButton()
{
	topLeft.setPoint(0,0);
	bottomRight.setPoint(0,0);
}
MenuButton::MenuButton(int tlX, int tlY, int brX, int brY)
{
	topLeft.setPoint(tlX,tlY);
	bottomRight.setPoint(brX,brY);
}
void MenuButton::drawButton()
{
	SDL_Rect source,destination;
	if(buttonPicture!=NULL)
	{
		source.x=0;
		source.y=0;
		source.h=buttonPicture->h;
		source.w=buttonPicture->w;
		destination.x=topLeft.x;
		destination.y=topLeft.y;
		destination.h=source.h;
		destination.w=source.w;
	}
}
bool MenuButton::isCursorHere(int mouseX, int mouseY)
{
	if(mouseX>topLeft.x&&mouseX<bottomRight.x&&mouseY>topLeft.y&&mouseY<bottomRight.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void MenuButton::setPicture(SDL_Surface* newPicture)
{
	buttonPicture=newPicture;
	bottomRight.setPoint(topLeft.x+newPicture->w,topLeft.y+newPicture->h);
}