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

//The game state
extern GameStates GAME_STATE;

//The renderer and window global objects
extern LWindow gWindow;
extern SDL_Renderer* gRenderer;

//A mapping of collision rects from the id of their game object
extern std::map<int, SDL_Rect> pageRects;

//The room variables
extern Room CURRENT_ROOM;
extern int ROOM_WIDTH;
extern int ROOM_HEIGHT;
extern int ROOM_NUMBER;

//The camera coordinates
extern int camX;
extern int camY;

//The main characters object
extern CharacterObject mainCharacter;