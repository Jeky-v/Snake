#include <SDL.h>
#include <SDL_image.h>
SDL_Surface* screen;
const int RESX=910,RESY=523;
const short N=65,M=35;
short map[N][M];
const short numberOfPictures=9;
SDL_Surface* pictures[numberOfPictures];
int loadPictures();
int drawMap();
int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_VIDEO);
	screen=SDL_SetVideoMode(RESX,RESY,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	loadPictures();

	SDL_Event event;
	
	bool exit=false;

	for (int i=0;i<N;i++)
		for (int j=0;j<M;j++)
			map[i][j]=4;

	while(!exit)
	{
		if (SDL_WaitEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
				{
					exit = true;
				}
				case SDL_KEYDOWN:
				{
					if ( event.key.keysym.sym == SDLK_ESCAPE ) 
					{
						exit=true;
					}	 
				}
			}
			drawMap();
			SDL_Flip(screen);
		}
	}
	SDL_Quit();
	return 0;
}
int loadPictures()
{	
	pictures[0]=IMG_Load("Pictures/Game/CellPic/cellsnake.1.14.png");
	pictures[1]=IMG_Load("Pictures/Game/CellPic/.png");
	pictures[2]=IMG_Load("Pictures/Game/CellPic/cellempty.14.png");
	pictures[3]=IMG_Load("Pictures/Game/CellPic/celleat.14.png");
	pictures[4]=IMG_Load("Pictures/Game/CellPic/cellwalldestructable.14.png");
	pictures[5]=IMG_Load("Pictures/Game/CellPic/cellwallundestructable.14.png");
	pictures[6]=IMG_Load("Pictures/Game/CellPic/cellreverse.14.png");	
	pictures[7]=IMG_Load("Pictures/Game/CellPic/cellteleport.14.png");
	pictures[8]=IMG_Load("Pictures/Game/CellPic/celleatgenerator.14.png");
	return 0;
}
int drawMap()
{
	for (int i=0;i<N;i++)
		for (int j=0;j<M;j++)
		{
			SDL_Rect source,destination;
			source.x=0;
			source.y=0;
			source.h=pictures[map[i][j]]->h;
			source.w=pictures[map[i][j]]->w;

			destination.h=pictures[map[i][j]]->h;
			destination.w=pictures[map[i][j]]->w;
			
			destination.x=i*pictures[map[i][j]]->w;
			destination.y=j*pictures[map[i][j]]->h;
			SDL_BlitSurface(pictures[map[i][j]],&source,screen,&destination);
		}
	return 0;
}