#pragma once

#include <SDL.h>

using namespace std;
#include <string>

class SpriteSheet
{
public:
	//Initializer
	SpriteSheet();

	//de-allocator
	~SpriteSheet();

	bool loadFromFile(std::string path);

	//de-allocate current texture
	void free();

	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setAlpha(Uint8 alpha);
	void setBlendMode(SDL_BlendMode blending);

	//renders texture
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	int getWidth();
	int getHeight();

private:
	//The loaded image
	SDL_Texture* mTexture;

	//The width and height of the whole sprite sheet
	int mWidth;
	int mHeight;
};

