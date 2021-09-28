#include "TextBox.h"

TextBox::TextBox() {
	defaultTextFont = nullptr;
}

TextBox::~TextBox() {
	free();
}

void TextBox::setFont(TTF_Font* textFont) {
	defaultTextFont = textFont;
}

bool TextBox::loadText(std::string textureText) {
	free();

	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(defaultTextFont, textureText.c_str(), { 0,0,0 }, SCREEN_WIDTH);

	if (textSurface == nullptr) {
		printf("unable to render text surface! SDL_tff Error: %s\n", TTF_GetError());
	}
	else {
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == nullptr) {
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else {
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}

	return mTexture != nullptr;
}

void TextBox::Render(SDL_Rect* clip) {

	int x = 0;
	int y = SCREEN_HEIGHT - mHeight;

	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	if (clip != nullptr) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

void TextBox::free() {
	if (mTexture != nullptr) {
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
	}
}

