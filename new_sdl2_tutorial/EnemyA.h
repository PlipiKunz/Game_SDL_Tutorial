#pragma once
#include "GameObject.h"
class EnemyA :
	public GameObject
{
public:
	EnemyA(int x = 0, int y = 0, int width = 20, int height = 20);
	void step(const Uint8* currentKeyStates);
private:
};

