#include "GameObject.h"
#include "globals.h"
#include "utils.h"

int GameObject::next_ID = 0;

GameObject::GameObject(bool collidable, int x, int y, int width, int height) {
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

void GameObject::setSpriteSheet(SpriteSheet* ss, bool useRect, SDL_Rect* sR) {
	mSpriteSheet = ss;

	if (useRect) {
		usingSpriteRect = true;
		mSpriteSheetRect = *sR;
	}
	setRectAndDimenions();
}

void GameObject::setRectAndDimenions() {

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

	mRect = { mPosX, mPosY, mWidth, mHeight };
	if (mCollidable) {
		pageRects[id] = mRect;
	}
}

void GameObject::render(int posX, int posY) {
	int drawAtX;
	int drawAtY;

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
		if (usingSpriteRect) {
			mSpriteSheet->render(drawAtX, drawAtY, &mSpriteSheetRect);
		}
		else {
			mSpriteSheet->render(drawAtX, drawAtY);
		}
	}
	else {
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0xFF, 0xFF);
		SDL_Rect adjustedRect = { drawAtX, drawAtY, mRect.w, mRect.h };
		SDL_RenderFillRect(gRenderer, &adjustedRect);
	}
}
