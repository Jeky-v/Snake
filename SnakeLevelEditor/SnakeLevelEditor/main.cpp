#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

SDL_Surface* screen;
const int RESX=910,RESY=540;
const short N=65,M=35;
short map[N][M];
const short numberOfPictures=9;
SDL_Surface* pictures[numberOfPictures];
SDL_Surface* bottomPicture;
int currentCellType=5;

int loadPictures();
int drawMap();
int drawBottom();
int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_VIDEO);
	screen=SDL_SetVideoMode(RESX,RESY,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	loadPictures();

	SDL_Event event;
	
	bool exit=false;
	bool isMouseButtonPressed=false;
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
					break;
				}
				case SDL_MOUSEBUTTONDOWN:
				{
					isMouseButtonPressed=true;
					int i=event.motion.x/pictures[0]->w;
					int j=event.motion.y/pictures[0]->h;
					if (j>=M) break;
					if (event.button.button==SDL_BUTTON_RIGHT) map[i][j]=0;//cell empty
					if (event.button.button==SDL_BUTTON_LEFT)  map[i][j]=currentCellType;
					break;
				}
				case SDL_MOUSEBUTTONUP:
				{
					isMouseButtonPressed=false;
					break;
				}
				case SDL_MOUSEMOTION:
				{
					if (isMouseButtonPressed)
					{
						int i=event.motion.x/pictures[0]->w;
						int j=event.motion.y/pictures[0]->h;
						if (j>=M) break;
						if (event.button.button==SDL_BUTTON_RIGHT) map[i][j]=0;//cell empty  don't work.
						if (event.button.button==SDL_BUTTON_LEFT)  map[i][j]=currentCellType;
					}
					break;
				}	
				case SDL_KEYDOWN:
				{
					if ( event.key.keysym.sym == SDLK_ESCAPE ) 
					{
						exit=true;
						break;
					}	 
				}
			}
			drawMap();
			drawBottom();
			SDL_Flip(screen);
		}
	}
	SDL_Quit();
	return 0;
}
int loadPictures()
{	
	pictures[0]=IMG_Load("Pictures/Game/CellPic/cellsnake.1.14.png");
	pictures[1]=IMG_Load("Pictures/Game/CellPic/cellsnake.2.14.png");
	pictures[2]=IMG_Load("Pictures/Game/CellPic/cellempty.14.png");
	pictures[3]=IMG_Load("Pictures/Game/CellPic/celleat.14.png");
	pictures[4]=IMG_Load("Pictures/Game/CellPic/cellwalldestructable.14.png");
	pictures[5]=IMG_Load("Pictures/Game/CellPic/cellwallundestructable.14.png");
	pictures[6]=IMG_Load("Pictures/Game/CellPic/cellreverse.14.png");	
	pictures[7]=IMG_Load("Pictures/Game/CellPic/cellteleport.14.png");
	pictures[8]=IMG_Load("Pictures/Game/CellPic/celleatgenerator.14.png");
	bottomPicture=IMG_Load("Pictures/Game/BottomPic/bottompicture.png");
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
int drawBottom()
{
	int y=M*pictures[0]->h+5;
	const short spaceBetween=80;
	const short leftSpace=RESX / 2 - (numberOfPictures / 2)*(pictures[0]->w+spaceBetween) ;
	SDL_Rect source,destination;
	source.x=0;
	source.y=0;
	source.h=bottomPicture->h;
	source.w=bottomPicture->w;
	destination.x=0;
	destination.y=RESY-50;
	destination.h=source.h;
	destination.w=source.w;
	SDL_BlitSurface(bottomPicture,&source,screen,&destination);
	for (int i=0;i<numberOfPictures;i++)
	{
			source.x=0;
			source.y=0;
			source.h=pictures[i]->h;
			source.w=pictures[i]->w;
			destination.h=pictures[i]->h;
			destination.w=pictures[i]->w;
			destination.x=leftSpace+i*(pictures[i]->w+spaceBetween);
			destination.y=y;
			SDL_BlitSurface(pictures[i],&source,screen,&destination);
	}
	return 0;
}