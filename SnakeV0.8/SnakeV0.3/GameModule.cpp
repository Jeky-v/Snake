#include "GameModule.h"
#include "GlobalVariables.h"
#include "ModuleName.h"
void GameModule::doPause()
{
	SDL_Event event;
	bool runPause=true;
	while(runPause)
	{
		if(SDL_WaitEvent(&event))
		{
		 
			switch(event.type)
			{
				case SDL_QUIT:
				{
					exit(0);
					break;
				}
				case SDL_KEYDOWN:
				{
					if ( event.key.keysym.sym == SDLK_ESCAPE ) 
					{
						m_mgr->SetActiveModule(MAINMENU);
						runPause=false;
					}	 
					if ( event.key.keysym.sym == SDLK_p || event.key.keysym.sym == SDLK_SPACE) 
					{
						runPause=false;
					} 
					break;
				}
			}
		}
	}
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
void GameModule::DrawText(int x, int y,const char *inputtext, int size, int R, int G, int B)
{
	TTF_Font* font = 0;
    font = TTF_OpenFont("Fonts/Neuropol Nova Bold.ttf",size);
	SDL_Color text_color = {R,G,B};

    SDL_Surface* blended_m = TTF_RenderUTF8_Blended(font, inputtext, text_color);
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
	TTF_CloseFont(font);
	SDL_FreeSurface(blended_m);
}