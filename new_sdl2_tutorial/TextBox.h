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

	void setFont(TTF_Font* textFont);

	bool loadText(std::string textureText);

	void step() {
	}

	void Render(SDL_Rect* clip = NULL);

	void free();

private:
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;


	int lines;
	int maxWidth;
	int maxHeight;

	TTF_Font* defaultTextFont;
};

