#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

#include <map>
#include "LWindow.h"

//Screen dimension constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern int ROOM_WIDTH;
extern int ROOM_HEIGHT;
extern int camX;
extern int camY;

extern LWindow gWindow;
extern SDL_Renderer* gRenderer;

extern TTF_Font* gFont;

extern std::map<int, SDL_Rect> pageRects;