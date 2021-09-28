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

	//the width and height of the window
	int mWidth;
	int mHeight;

	//various tracked window properties
	bool mMouseFocus;
	bool mKeyboardFocus;
	bool mFullScreen;
	bool mMinimized;
};

