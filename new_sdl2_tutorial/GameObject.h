#pragma once

#include <SDL.h>

class GameObject
{
public:
	//a global static id which should be unique
	static int next_ID;

	static const int MAX_VELOCITY = 5;
	//the max velocity allowed in any direction
	static enum Direction { left, down, right, up };

	GameObject(int x = 0, int y = 0, int width = 20, int height = 20, bool collidable = true);

	void step(const Uint8* currentKeyStates);

	void render(int posX = NULL, int posY = NULL);

	void setPos(int x, int y);

	int getID() { return this->id; };
	int getX() { return this->mPosX; };
	int getY() { return this->mPosY; };
	SDL_Rect getRect() { return this->mRect; };

protected:
	int id;

	bool mCollidable;

	//the velocity vector of the object, x, y,
	int mVelocity[2];
	Direction mDirection;

	int mPosX, mPosY;
	int mWidth = 20;
	int mHeight = 20;

	SDL_Rect mRect;

	void handleKeyPresses(const Uint8* currentKeyStates);
	void setRectAndDimenions();
	void move();
};

