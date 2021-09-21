#include "TextBox.h"

TextBox::TextBox() {
}

TextBox::~TextBox() {
	free();
}

bool TextBox::loadText(std::string textureText, TTF_Font* textFont, SDL_Color textColor) {
	free();

	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(textFont, textureText.c_str(), textColor, SCREEN_WIDTH);
	if (textSurface == NULL) {
		printf("unable to render text surface! SDL_tff Error: %s\n", TTF_GetError());
	}
	else {
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL) {
			printf("Unable to create textuer from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else {
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}

	return mTexture != NULL;
}

void TextBox::Render(SDL_Rect* clip) {

	int x = 0;
	int y = SCREEN_HEIGHT - mHeight;

	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

void TextBox::free() {
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
	}
}

