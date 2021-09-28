#include "GameObject.h"
#include "globals.h"
#include "utils.h"

int GameObject::next_ID = 0;

GameObject::GameObject(bool collidable, int x, int y, int width, int height) {
	mPosX = x;
	mPosY = y;
	mWidth = width;
	mHeight = height;

	//sets collidability of the object
	mCollidable = collidable;

	//Sets direction down by default
	mDirection = Direction::down;

	//Sets velocity to zero to start
	mVelocity[0] = 0;
	mVelocity[1] = 0;

	//sets the id, then increments it so that the id will be unique
	id = next_ID;
	next_ID += 1;

	//sets the rectangle
	setRectAndDimenions();
}

void GameObject::step(const Uint8* currentKeyStates) {
	handleKeyPresses(currentKeyStates);
	move();
}

void  GameObject::handleKeyPresses(const Uint8* currentKeyStates) {
}

void GameObject::move() {

	//Moves in the x direction and updates the rectangle
	mPosX += mVelocity[0];
	setRectAndDimenions();
	//Collision checks after moving in x, and if collision, undoes the movement
	if (mCollidable && checkAllCollisions(id, mRect)) {
		mPosX -= mVelocity[0];
		setRectAndDimenions();
	}

	//Moves in the y direction and updates rectangle
	mPosY += mVelocity[1];
	setRectAndDimenions();
	//Collision checks after moving in y, and if collision, undoes the movement
	if (mCollidable && checkAllCollisions(id, mRect)) {
		mPosY -= mVelocity[1];
		setRectAndDimenions();
	}
}

void GameObject::setPos(int x, int y) {
	//Sets the position then updates rectangle
	mPosX = x;
	mPosY = y;
	setRectAndDimenions();
}

void GameObject::setSpriteSheet(SpriteSheet* ss, bool useRect, SDL_Rect* sR) {
	//Sets the objects sprite sheet and sprite sheet rectangle
	mSpriteSheet = ss;

	if (useRect) {
		usingSpriteRect = true;
		mSpriteSheetRect = *sR;
	}
	setRectAndDimenions();
}

void GameObject::setRectAndDimenions() {
	//Updates the dimensions
	if (mSpriteSheet) {
		if (usingSpriteRect) {
			mWidth = mSpriteSheetRect.w;
			mHeight = mSpriteSheetRect.h;
		}
		else {
			mWidth = mSpriteSheet->getWidth();
			mHeight = mSpriteSheet->getHeight();
		}
	}

	//Sets the rectangle
	mRect = { mPosX, mPosY, mWidth, mHeight };

	//If the object should be collidable, adds it to or updates its entry
	if (mCollidable) {
		pageRects[id] = mRect;
	}
}

void GameObject::render(int posX, int posY) {
	int drawAtX;
	int drawAtY;

	//Adjusts the drawing to either given location, or the normal x and y locations with camera offset
	if (posX != NULL && posY != NULL) {
		drawAtX = posX;
		drawAtY = posY;
	}
	else {
		drawAtX = mRect.x;
		drawAtY = mRect.y;

		drawAtX = drawAtX - camX;
		drawAtY = drawAtY - camY;
	}


	if (mSpriteSheet) {
		//Renders the sprite sheet
		if (usingSpriteRect) {
			mSpriteSheet->render(drawAtX, drawAtY, &mSpriteSheetRect);
		}
		else {
			mSpriteSheet->render(drawAtX, drawAtY);
		}
	}
	else {
		//renders a default rectangle
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0xFF, 0xFF);
		SDL_Rect adjustedRect = { drawAtX, drawAtY, mRect.w, mRect.h };
		SDL_RenderFillRect(gRenderer, &adjustedRect);
	}
}
