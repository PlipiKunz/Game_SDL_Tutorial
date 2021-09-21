#pragma once
#include "GameObject.h"
class CharacterObject :
	public GameObject
{
public:
	CharacterObject(int x = 0, int y = 0, int width = 20, int height = 20);

	void step(const Uint8* currentKeyStates);

	void render();

protected:
	void handleKeyPresses(const Uint8* currentKeyStates);
};

