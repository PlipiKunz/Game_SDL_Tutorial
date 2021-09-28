#pragma once
#include <SDL.h>

bool checkAllCollisions(int idA, SDL_Rect rectA);
bool checkCollision(SDL_Rect rectA, SDL_Rect rectB);

//the direction enums used by game objects to represent what direction they are facing
static enum class Direction { left, down, right, up };

//the game state enum used by the game state machine
static enum class GameStates { normal, text_box };