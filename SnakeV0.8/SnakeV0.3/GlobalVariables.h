#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "CellTypeConverter.h"
#include "Cell.h"
#include "ModuleMgr.h"

class Cell;
class CellTypeConverter;

extern SDL_Surface *screen;
extern bool full_screen_mode;
extern int RESX;
extern int RESY;
extern int musicVolume;
extern int soundVolume;
extern SDL_Surface* cell_pic[9];
extern CellTypeConverter Converter;
extern Cell *global_map[65][35];
extern ModuleMgr mgr;
extern Mix_Chunk* sounds[5];