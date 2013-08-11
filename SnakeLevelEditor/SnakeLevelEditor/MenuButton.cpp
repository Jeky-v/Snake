#include "MenuButton.h"

MenuButton::MenuButton()
{
	topLeft.setPoint(0,0);
	bottomRight.setPoint(0,0);
	cursorHere = false;
}
MenuButton::MenuButton(int tlX, int tlY, int brX, int brY)
{
	topLeft.setPoint(tlX,tlY);
	bottomRight.setPoint(brX,brY);
	cursorHere = false;
}
MenuButton::MenuButton(int tlX, int tlY, SDL_Surface* newPicture)
{
	topLeft.setPoint(tlX, tlY);
	buttonPicture=newPicture;
	bottomRight.setPoint(topLeft.x+newPicture->w,topLeft.y+newPicture->h);
	cursorHere = false;
}
void MenuButton::drawButton(SDL_Surface* destinationSurface)
{
	SDL_Rect source,destination;
	if(buttonPicture!=NULL)
	{
		source.x=0;
		if(cursorHere)
		{
			source.y=buttonPicture->h/2;
		}
		else
		{
			source.y=0;
		}		
		source.h=buttonPicture->h/2;
		source.w=buttonPicture->w;	
		destination.x=topLeft.x;
		destination.y=topLeft.y;
		destination.h=source.h;
		destination.w=source.w;
		SDL_BlitSurface(buttonPicture, &source, destinationSurface, &destination);
	}
}
bool MenuButton::isCursorHere(int mouseX, int mouseY)
{
	if(mouseX>topLeft.x&&mouseX<bottomRight.x&&mouseY>topLeft.y&&mouseY<bottomRight.y)
	{
		cursorHere = true;
		return true;
	}
	else
	{
		cursorHere = false;
		return false;
	}
}
void MenuButton::setPicture(SDL_Surface* newPicture)
{
	buttonPicture=newPicture;
	bottomRight.setPoint(topLeft.x+newPicture->w,topLeft.y+newPicture->h);
}