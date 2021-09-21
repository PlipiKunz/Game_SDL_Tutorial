#pragma once

#include <SDL.h>

class LWindow
{
public:
	LWindow();

	bool init();

	SDL_Renderer* createRenderer();

	void handleEvent(SDL_Event& e);

	void free();

	int getWidth() { return mWidth; }
	int getHeight() { return mHeight; }

	bool hasMouseFocus() { return mMouseFocus; }
	bool hasKeyboardFocus() { return mKeyboardFocus; }
	bool isMinimized() { return mMinimized; }

private:
	SDL_Window* mWindow;

	int mWidth;
	int mHeight;

	bool mMouseFocus;
	bool mKeyboardFocus;
	bool mFullScreen;
	bool mMinimized;
};

