#pragma once

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

#include "globals.h"


class TextBox
{
public:
	TextBox();
	~TextBox();

	bool loadText(std::string textureText, TTF_Font* textFont, SDL_Color textColor);

	void Render(SDL_Rect* clip = NULL);

	void free();

private:
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
};

