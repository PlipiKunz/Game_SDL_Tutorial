#include <SDL_image.h>

#include "SpriteSheet.h"
#include "globals.h"

#include <iostream>

//Initializer
SpriteSheet::SpriteSheet() {
	mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;
}

//de-allocator
SpriteSheet::~SpriteSheet() {
	free();
}

bool SpriteSheet::loadFromFile(std::string path) {
	free();

	path = "Images/" + path;

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixel
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else {
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	mTexture = newTexture;

	//returns if the texture was successfully initialized
	return (mTexture != NULL);
}

//de-allocate current texture
void SpriteSheet::free() {
	//Free texture if it exists
	if (this != nullptr) {
		if (mTexture != nullptr) {
			SDL_DestroyTexture(mTexture);
			mTexture = nullptr;
			mWidth = 0;
			mHeight = 0;
		}
	}

}

void SpriteSheet::setColor(Uint8 red, Uint8 green, Uint8 blue) {
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}
void SpriteSheet::setAlpha(Uint8 alpha) {
	SDL_SetTextureAlphaMod(mTexture, alpha);
}
void SpriteSheet::setBlendMode(SDL_BlendMode bm) {
	SDL_SetTextureAlphaMod(mTexture, bm);
}

void SpriteSheet::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	//renders texture
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	if (clip != nullptr) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int SpriteSheet::getWidth() {
	return mWidth;
}

int SpriteSheet::getHeight() {
	return mHeight;
}

