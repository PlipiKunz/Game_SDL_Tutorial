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

	bool load();
	bool loadMedia();
	bool loadObjects();

	void free();

	void step(const Uint8* currentKeyStates);

	void render();

	int getRoomWidth() { return mWidth; }
	int getRoomHeight() { return mHeight; }

private:
	int mWidth;
	int mHeight;

	std::map<string, GameObject*> mGameObjects = {};
	std::map<string, SpriteSheet*> mSpriteSheets = {};
};

