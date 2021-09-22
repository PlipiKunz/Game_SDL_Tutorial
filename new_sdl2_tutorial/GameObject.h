#pragma once
#include "SpriteSheet.h"
#include <SDL.h>
#include<optional>


class GameObject
{
public:
	//a global static id which should be unique
	static int next_ID;

	static const int MAX_VELOCITY = 5;
	//the max velocity allowed in any direction
	static enum Direction { left, down, right, up };

	GameObject(bool collidable = true, int x = 0, int y = 0, int width = 20, int height = 20);

	void step(const Uint8* currentKeyStates);

	void render(int posX = NULL, int posY = NULL);

	void setPos(int x, int y);
	void setSpriteSheet(SpriteSheet* sS, bool useRect = false, SDL_Rect* sR = NULL);

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

	SpriteSheet* mSpriteSheet;

	bool usingSpriteRect = false;
	SDL_Rect mSpriteSheetRect;
};

