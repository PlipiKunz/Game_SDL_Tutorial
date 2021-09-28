#pragma once

#include <SDL.h>
#include <map>
#include <string>

#include "GameObject.h"
#include "SpriteSheet.h"

class Room
{
public:
	Room();
	~Room();

	bool load();
	bool loadMedia();
	bool loadObjects();

	void free();

	void step(const Uint8* currentKeyStates);

	void render();

	int getRoomWidth() { return mWidth; }
	int getRoomHeight() { return mHeight; }

private:
	//the rooms dimensions
	int mWidth;
	int mHeight;

	//a map of game objects indexed into using the name
	std::map<string, GameObject*> mGameObjects = {};
	//a map of spritesheets indexed into using the name
	std::map<string, SpriteSheet*> mSpriteSheets = {};
};

