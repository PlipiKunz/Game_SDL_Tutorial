#pragma once

#include <SDL.h>
#include "globals.h"
#include "GameObject.h"

class Room
{
public:
	Room();

	bool init();
	void close();

	void step(const Uint8* currentKeyStates);
	void render();

private:
	int mWidth;
	int mHeight;
	GameObject mMovables[];
};

