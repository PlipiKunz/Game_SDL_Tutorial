#include "GameObject.h"
#include "globals.h"
#include "utils.h"

int GameObject::next_ID = 0;

GameObject::GameObject(int x, int y, int width, int height, bool collidable) {
	mDirection = down;

	mVelocity[0] = 0;
	mVelocity[1] = 0;

	mPosX = x;
	mPosY = y;
	mWidth = width;
	mHeight = height;

	mCollidable = collidable;

	id = next_ID;
	next_ID += 1;
	setRectAndDimenions();
}
void GameObject::step(const Uint8* currentKeyStates) {
	handleKeyPresses(currentKeyStates);
	move();
}

void  GameObject::handleKeyPresses(const Uint8* currentKeyStates) {
}

void GameObject::move() {
	mPosX += mVelocity[0];
	setRectAndDimenions();

	if (mCollidable && checkAllCollisions(id, mRect)) {
		mPosX -= mVelocity[0];
		setRectAndDimenions();
	}

	mPosY += mVelocity[1];
	setRectAndDimenions();
	if (mCollidable && checkAllCollisions(id, mRect)) {
		mPosY -= mVelocity[1];
		setRectAndDimenions();
	}
}

void GameObject::setPos(int x, int y) {
	mPosX = x;
	mPosY = y;
	setRectAndDimenions();
}

void GameObject::setRectAndDimenions() {
	mRect = { mPosX, mPosY, mWidth, mHeight };

	if (mCollidable) {
		pageRects[id] = mRect;
	}
}

void GameObject::render(int posX, int posY) {

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0xFF, 0xFF);

	int drawAtX;
	int drawAtY;

	if (posX != NULL && posY != NULL) {
		drawAtX = posX;
		drawAtY = posY;
	}
	else {
		drawAtX = mRect.x;
		drawAtY = mRect.y;
	}

	SDL_Rect adjustedRect = { drawAtX - camX, drawAtY - camY, mRect.w, mRect.h };
	SDL_RenderFillRect(gRenderer, &adjustedRect);
}
