#include "CharacterObject.h"
#include "globals.h"

CharacterObject::CharacterObject(int x, int y, int width, int height) :GameObject::GameObject(x, y, width, height, true) {

}

void CharacterObject::step(const Uint8* currentKeyStates) {
	handleKeyPresses(currentKeyStates);
	move();
}

void CharacterObject::handleKeyPresses(const Uint8* currentKeyStates) {
	mVelocity[0] = 0;
	mVelocity[1] = 0;

	bool keepDirection = false;
	Direction prevDirection = mDirection;

	if (currentKeyStates[SDL_SCANCODE_LEFT]) {
		mVelocity[0] -= MAX_VELOCITY;

		if (!keepDirection) {
			Direction direction = left;
			mDirection = direction;
			if (prevDirection == direction) {
				keepDirection = true;
			}
		}
	}
	if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
		mVelocity[0] += MAX_VELOCITY;

		if (!keepDirection) {
			Direction direction = right;
			mDirection = direction;
			if (prevDirection == direction) {
				keepDirection = true;
			}
		}
	}
	if (currentKeyStates[SDL_SCANCODE_DOWN]) {
		mVelocity[1] += MAX_VELOCITY;

		if (!keepDirection) {
			Direction direction = down;
			mDirection = direction;
			if (prevDirection == direction) {
				keepDirection = true;
			}
		}
	}
	if (currentKeyStates[SDL_SCANCODE_UP]) {
		mVelocity[1] -= MAX_VELOCITY;

		if (!keepDirection) {
			Direction direction = up;
			mDirection = direction;
			if (prevDirection == direction) {
				keepDirection = true;
			}
		}
	}
}

void CharacterObject::render() {
	if (mDirection == left) {
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	}
	if (mDirection == right) {
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
	}
	if (mDirection == down) {
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
	}
	if (mDirection == up) {
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	}

	SDL_Rect adjustedRect = { mRect.x - camX, mRect.y - camY, mRect.w, mRect.h };
	SDL_RenderFillRect(gRenderer, &adjustedRect);
}