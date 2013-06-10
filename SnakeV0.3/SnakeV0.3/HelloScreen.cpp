#include "GlobalVariables.h"

#include "HelloScreen.h"
#include "ModuleName.h"
#include "ModuleMgr.h"


void HelloScreen::DrawText(int x,int y,char *inputtext,int size,int R,int G,int B)
{
	TTF_Font* font = 0;
    font = TTF_OpenFont("Fonts/Komika.ttf",size);
	SDL_Color text_color = {R,G,B};
    char* text = inputtext; 

    SDL_Surface* blended_m = TTF_RenderUTF8_Blended(font, text, text_color);
	SDL_Rect dst;
    dst.x = x;
	dst.y = y;
	dst.w = blended_m->w;
	dst.h = blended_m->h;
    SDL_Rect src;
    src.x = 0;       
	src.y = 0;
	src.w=dst.w;
	src.h=dst.h;
	SDL_BlitSurface(blended_m,&src,screen,&dst);
	SDL_Flip(screen);
}

void HelloScreen::doInit()
{
	if(full_screen_mode)
	{ Logo=IMG_Load("Pictures/HelloScreen/Helloscreen.1366.png"); }
	else
	{ Logo=IMG_Load("Pictures/HelloScreen/Helloscreen.900.png"); }
}

bool HelloScreen::doRun()
{
	SDL_Rect dest,sour;
	sour.x=0;
	sour.y=0;
	sour.h=Logo->h;
	sour.w=Logo->w;
	dest=sour;

	SDL_BlitSurface(Logo,&sour,screen,&dest);
	DrawText(10,5,"Press any key to continue",50,250,152,5);
	
	SDL_Flip(screen);
	SDL_Event event;
	SDL_WaitEvent(&event);
	if (event.type == SDL_QUIT)
		{return false;}
	if (event.type == SDL_KEYDOWN)
			{
				if ( event.key.keysym.sym == SDLK_ESCAPE ) 
				{
					return false;
				} 
				else
				{
					m_mgr->SetActiveModule(MAINMENU);
				}
			}
	return true;
}

void HelloScreen::doClose()
{
	SDL_FreeSurface(Logo);
}

