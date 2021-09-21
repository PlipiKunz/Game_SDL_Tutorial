#pragma once
#include <SDL.h>

class Tile
{
public:
	Tile(int x, int y, int tileWidth, int tileHeight, int tileType);

	void render();

	int getType() { return mType; };

	SDL_Rect getRect() { return mBox; };

private:
	SDL_Rect mBox;

	int mType;
};

