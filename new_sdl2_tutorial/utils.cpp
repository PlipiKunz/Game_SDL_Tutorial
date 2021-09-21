#include "utils.h"
#include "globals.h"

bool checkAllCollisions(int idA, SDL_Rect rectA) {

	for (auto pair = pageRects.begin(); pair != pageRects.end(); pair++) {
		if (idA != pair->first) {
			SDL_Rect rectB = pair->second;

			if (checkCollision(rectA, rectB)) {
				return true;
			}
		}
	}

	return false;
}

bool checkCollision(SDL_Rect rectA, SDL_Rect rectB) {
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = rectA.x;
	rightA = rectA.x + rectA.w;
	topA = rectA.y;
	bottomA = rectA.y + rectA.h;

	leftB = rectB.x;
	rightB = rectB.x + rectB.w;
	topB = rectB.y;
	bottomB = rectB.y + rectB.h;

	if (bottomA <= topB) {
		return false;
	}
	if (topA >= bottomB) {
		return false;
	}
	if (rightA <= leftB) {
		return false;
	}
	if (leftA >= rightB) {
		return false;
	}

	return true;
}