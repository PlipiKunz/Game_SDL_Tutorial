#include "LWindow.h"
#include "globals.h"
#include <sstream>
#include <iostream>
#include <SDL.h>

LWindow::LWindow()
{
	mWindow = nullptr;
	mMouseFocus = false;
	mKeyboardFocus = false;
	mFullScreen = false;
	mMinimized = false;
	mWidth = 0;
	mHeight = 0;
}

bool LWindow::init()
{
	//Creates a resizable window
	mWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (mWindow != nullptr)
	{
		mMouseFocus = true;
		mKeyboardFocus = true;
		mWidth = SCREEN_WIDTH;
		mHeight = SCREEN_HEIGHT;
	}
	return  mWindow != nullptr;
}

SDL_Renderer* LWindow::createRenderer() {
	SDL_Renderer* renderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	return renderer;
}

void LWindow::handleEvent(SDL_Event& e) {
	if (e.type == SDL_WINDOWEVENT) {
		bool focusChange = false;
		switch (e.window.event) {
		case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent(gRenderer);
			break;

		case SDL_WINDOWEVENT_ENTER:
			mMouseFocus = true;
			focusChange = true;
			break;

		case SDL_WINDOWEVENT_LEAVE:
			mMouseFocus = false;
			focusChange = true;
			break;

		case SDL_WINDOWEVENT_FOCUS_GAINED:
			mKeyboardFocus = true;
			focusChange = true;
			break;

		case SDL_WINDOWEVENT_FOCUS_LOST:
			mKeyboardFocus = false;
			focusChange = true;
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
			mMinimized = true;
			break;

		case SDL_WINDOWEVENT_MAXIMIZED:
			mMinimized = false;
			break;

		case SDL_WINDOWEVENT_RESTORED:
			mMinimized = false;
			break;
		}

		if (focusChange) {
			std::stringstream caption;
			caption << "SDL Tutorial - MouseFocus:" << ((mMouseFocus) ? "On" : "Off") << " KeyboardFocus:" << ((mKeyboardFocus) ? "On" : "Off");
			SDL_SetWindowTitle(mWindow, caption.str().c_str());
		}
	}
}

void LWindow::free() {
	SDL_DestroyWindow(mWindow);
	mWindow = nullptr;
}