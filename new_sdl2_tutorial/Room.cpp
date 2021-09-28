#include "Room.h"
#include "EnemyA.h"
#include "globals.h"

#include <iostream>

Room::Room() {
	ROOM_WIDTH = mWidth = SCREEN_WIDTH * 2;
	ROOM_HEIGHT = mHeight = SCREEN_HEIGHT * 2;
}

Room::~Room() {
	if (this != nullptr) {
		free();
	}
}

bool Room::load() {
	mainCharacter.setPos(0, 0);

	return loadMedia() && loadObjects();
}

bool Room::loadMedia() {
	//Loading success flag
	bool success = true;

	mSpriteSheets["Foo"] = new SpriteSheet();
	mSpriteSheets["Background"] = new SpriteSheet();
	mSpriteSheets["Circles"] = new SpriteSheet();

	//Load Foo' texture
	if (!mSpriteSheets["Foo"]->loadFromFile("foo.png"))
	{
		printf("Failed to load Foo' texture image!\n");
		success = false;
	}

	//Load background texture
	if (!mSpriteSheets["Background"]->loadFromFile("background.png"))
	{
		printf("Failed to load background texture image!\n");
		success = false;
	}
	else {
		mSpriteSheets["Background"]->setBlendMode(SDL_BLENDMODE_BLEND);
		mSpriteSheets["Background"]->setAlpha(0x55);
	}

	//Load the circle sprite sheet
	if (!mSpriteSheets["Circles"]->loadFromFile("dots.png"))
	{
		printf("Failed to load sprite sheet texture!\n");
		success = false;
	}

	return success;
}

bool Room::loadObjects() {
	bool success = true;

	SDL_Rect gSpriteClips[4] = {};
	if (mSpriteSheets.find("Circles") != mSpriteSheets.end()) {
		SpriteSheet* gCircleTexture = mSpriteSheets["Circles"];

		//Set top left sprite
		gSpriteClips[0].x = 0;
		gSpriteClips[0].y = 0;
		gSpriteClips[0].w = 100;
		gSpriteClips[0].h = 100;

		mGameObjects["tlC"] = new GameObject(false);
		mGameObjects["tlC"]->setSpriteSheet(gCircleTexture, true, &gSpriteClips[0]);
		mGameObjects["tlC"]->setPos(0, 0);


		//Set top right sprite
		gSpriteClips[1].x = 100;
		gSpriteClips[1].y = 0;
		gSpriteClips[1].w = 100;
		gSpriteClips[1].h = 100;

		mGameObjects["trC"] = new GameObject(false);
		mGameObjects["trC"]->setSpriteSheet(gCircleTexture, true, &gSpriteClips[1]);
		mGameObjects["trC"]->setPos(SCREEN_WIDTH - gSpriteClips[1].w - camX, 0 - camY);



		//Set bottom left sprite
		gSpriteClips[2].x = 0;
		gSpriteClips[2].y = 100;
		gSpriteClips[2].w = 100;
		gSpriteClips[2].h = 100;

		mGameObjects["blC"] = new GameObject(false);
		mGameObjects["blC"]->setSpriteSheet(gCircleTexture, true, &gSpriteClips[2]);
		mGameObjects["blC"]->setPos(0 - camX, SCREEN_HEIGHT - gSpriteClips[2].h - camY);



		//Set bottom right sprite
		gSpriteClips[3].x = 100;
		gSpriteClips[3].y = 100;
		gSpriteClips[3].w = 100;
		gSpriteClips[3].h = 100;

		mGameObjects["brC"] = new GameObject(false);
		mGameObjects["brC"]->setSpriteSheet(gCircleTexture, true, &gSpriteClips[3]);
		mGameObjects["brC"]->setPos(SCREEN_WIDTH - gSpriteClips[3].w - camX, SCREEN_HEIGHT - gSpriteClips[3].h - camY);
	}
	else {
		success = false;
	}

	mGameObjects["bL"] = new GameObject(true, 0, 0, 0, ROOM_HEIGHT);
	mGameObjects["bR"] = new GameObject(true, ROOM_WIDTH, 0, 0, ROOM_HEIGHT);
	mGameObjects["bU"] = new GameObject(true, 0, 0, ROOM_WIDTH, 0);
	mGameObjects["bD"] = new GameObject(true, 0, ROOM_HEIGHT, ROOM_WIDTH, 0);

	if (mSpriteSheets.find("Foo") != mSpriteSheets.end()) {
		SpriteSheet* Foo = mSpriteSheets["Foo"];
		mGameObjects["en"] = new EnemyA();
		mGameObjects["en"]->setPos(ROOM_WIDTH / 2, ROOM_HEIGHT / 2);
		mGameObjects["en"]->setSpriteSheet(Foo);
	}
	else {
		success = false;
	}

	return success;
}

void Room::free() {
	for (auto x : mSpriteSheets) {
		x.second->free();
		mSpriteSheets[x.first] = nullptr;

	}

	for (auto x : mGameObjects) {
		mGameObjects[x.first] = nullptr;
	}
}

void Room::step(const Uint8* currentKeyStates) {
	mainCharacter.step(currentKeyStates);

	// Updates the camera to focus on the main character
	camX = mainCharacter.getX() - (SCREEN_WIDTH / 2);
	camY = mainCharacter.getY() - (SCREEN_HEIGHT / 2);

	// Keeps the camera in bounds
	if (camX < 0) {
		camX = 0;
	}
	if (camX > ROOM_WIDTH - SCREEN_WIDTH) {
		camX = ROOM_WIDTH - SCREEN_WIDTH;
	}
	if (camY < 0) {
		camY = 0;
	}
	if (camY > ROOM_HEIGHT - SCREEN_HEIGHT) {
		camY = ROOM_HEIGHT - SCREEN_HEIGHT;
	}
}

void Room::render() {
	//renders the various objects

	if (mSpriteSheets.find("Background") != mSpriteSheets.end()) {
		mSpriteSheets["Background"]->render(0, 0);
	}

	if (mGameObjects.find("tlC") != mGameObjects.end()) {
		mGameObjects["tlC"]->render();
	}
	if (mGameObjects.find("trC") != mGameObjects.end()) {
		mGameObjects["trC"]->render();
	}

	if (mGameObjects.find("blC") != mGameObjects.end()) {
		mGameObjects["blC"]->render();
	}

	if (mGameObjects.find("brC") != mGameObjects.end()) {
		mGameObjects["brC"]->render();
	}

	if (mGameObjects.find("en") != mGameObjects.end()) {
		mGameObjects["en"]->render();
	}

	mainCharacter.render();
}