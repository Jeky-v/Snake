#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Game.h"

extern SDL_Surface *screen;
extern bool full_screen_mode;
extern int RESX;
extern int RESY;
extern SDL_Surface* cell_pic[8];
extern Game *game_module_p;
