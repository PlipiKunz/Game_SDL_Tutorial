#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

#include <map>
#include "LWindow.h"
#include "Room.h"
#include "CharacterObject.h"

//Screen dimension constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;


extern CharacterObject mainCharacter;

//extern int ROOM_NUMBER;
extern Room CURRENT_ROOM;
extern int ROOM_WIDTH;
extern int ROOM_HEIGHT;

extern int camX;
extern int camY;

extern LWindow gWindow;
extern SDL_Renderer* gRenderer;

extern TTF_Font* gFont;

extern std::map<int, SDL_Rect> pageRects;