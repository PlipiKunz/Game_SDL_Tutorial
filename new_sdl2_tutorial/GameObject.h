#pragma once
#include "SpriteSheet.h"
#include "utils.h"

#include <SDL.h>
#include <optional>


class GameObject
{
public:
	//a global static id which should be unique
	static int next_ID;

	//the max velocity allowed in any direction
	static const int MAX_VELOCITY = 5;

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
	//the unique identifier 
	int id;

	//if the object is collidable
	bool mCollidable;

	//the velocity vector of the object, x, y,
	int mVelocity[2];
	Direction mDirection;

	//the position variables
	int mPosX, mPosY;
	int mWidth = 20;
	int mHeight = 20;

	//the rectangle representing the position of the object for rendering and collision
	SDL_Rect mRect;

	//the optional spritesheet
	SpriteSheet* mSpriteSheet;

	//the optional subsection of the rectangle that should be used
	bool usingSpriteRect = false;
	SDL_Rect mSpriteSheetRect;


	void handleKeyPresses(const Uint8* currentKeyStates);
	void setRectAndDimenions();
	void move();
};

