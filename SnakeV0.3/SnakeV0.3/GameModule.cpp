#include "GameModule.h"
#include "GlobalVariables.h"

void GameModule::Pause()
{
}

void GameModule::DrawField()
{
	for (int i=0;i<65;i++)
	{
		for(int j=0;j<35;j++)
		{
			if(global_map[i][j]!=NULL)
			{
				global_map[i][j]->DrawCell();
			}
		}
	}
	SDL_Flip(screen);
}

void GameModule::DrawText(int x, int y, char *inputtext, int size, int R, int G, int B)
{
	TTF_Font* font = 0;
    font = TTF_OpenFont("Fonts/AbductionCyr.ttf",size);
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