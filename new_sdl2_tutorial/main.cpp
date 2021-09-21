#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <string>

#include <iostream>

#include "SpriteSheet.h"
#include "TextBox.h"
#include "globals.h"
#include "GameObject.h"
#include "CharacterObject.h"
#include "LWindow.h"

//Tutorial: https://lazyfoo.net/tutorials/SDL/index.php

//True Global variable declaractions any file can access
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
int ROOM_WIDTH = 1280;
int ROOM_HEIGHT = 960;
int camX = 0;
int camY = 0;

LWindow gWindow = LWindow();
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;
std::map<int, SDL_Rect> pageRects = {};


//Local global variable declarations for this file to access
TextBox gTextBox;

SpriteSheet gFooTexture;
SpriteSheet gBackgroundTexture;
SDL_Rect gSpriteClips[4];
SpriteSheet gSpriteSheetTexture;

bool init()
{

	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		if (!gWindow.init())
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = gWindow.createRenderer();
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1) {
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load Foo' texture
	if (!gFooTexture.loadFromFile("foo.png"))
	{
		printf("Failed to load Foo' texture image!\n");
		success = false;
	}

	//Load background texture
	if (!gBackgroundTexture.loadFromFile("background.png"))
	{
		printf("Failed to load background texture image!\n");
		success = false;
	}
	else {
		gBackgroundTexture.setBlendMode(SDL_BLENDMODE_BLEND);
	}

	//Load the sprite sheet
	if (!gSpriteSheetTexture.loadFromFile("dots.png"))
	{
		printf("Failed to load sprite sheet texture!\n");
		success = false;
	}
	else
	{
		//Set top left sprite
		gSpriteClips[0].x = 0;
		gSpriteClips[0].y = 0;
		gSpriteClips[0].w = 100;
		gSpriteClips[0].h = 100;

		//Set top right sprite
		gSpriteClips[1].x = 100;
		gSpriteClips[1].y = 0;
		gSpriteClips[1].w = 100;
		gSpriteClips[1].h = 100;

		//Set bottom left sprite
		gSpriteClips[2].x = 0;
		gSpriteClips[2].y = 100;
		gSpriteClips[2].w = 100;
		gSpriteClips[2].h = 100;

		//Set bottom right sprite
		gSpriteClips[3].x = 100;
		gSpriteClips[3].y = 100;
		gSpriteClips[3].w = 100;
		gSpriteClips[3].h = 100;
	}

	//Load the textbox
	gFont = TTF_OpenFont("Fonts/lazy.ttf", 28);
	if (gFont == NULL) {
		printf("Failed to load lazy font! SDL_ttf Error %s\n", TTF_GetError());
		success = false;
	}
	else {
		SDL_Color textColor = { 0,0,0 };
		if (!gTextBox.loadText("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aliquam iaculis quis erat eu hendrerit. Nam eu vulputate ligula, id fermentum tortor. Aliquam molestie ornare fringilla. Quisque posuere sit amet purus a eleifend. Donec dapibus tempor pretium. Nam elementum vulputate ipsum tempus aliquam. Proin laoreet enim sit amet leo mollis convallis ut non elit. Aliquam elementum libero tellus, at pretium purus scelerisque sed.", gFont, textColor)) {
			printf("Failed to render text texture!\n");
			success = false;
		}
	}


	return success;
}

void close()
{
	//Free loaded images
	gFooTexture.free();
	gBackgroundTexture.free();
	gSpriteSheetTexture.free();


	//remove the textbox
	gTextBox.free();

	//cleanup font
	TTF_CloseFont(gFont);
	gFont = NULL;

	//Destroy window    
	gWindow.free();
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Start up SDL and create window, and load media
	if (!init() || !loadMedia())
	{
		printf("Failed to initialize or load media!\n");
		close();
		return 0;
	}

	Uint8 foregroundAlpha = 255;

	GameObject screenBarrierL = GameObject(0, 0, 0, ROOM_HEIGHT);
	GameObject screenBarrierR = GameObject(ROOM_WIDTH, 0, 0, ROOM_HEIGHT);
	GameObject screenBarrierU = GameObject(0, 0, ROOM_WIDTH, 0);
	GameObject screenBarrierD = GameObject(0, ROOM_HEIGHT, ROOM_WIDTH, 0);

	CharacterObject character = CharacterObject();
	character.setPos(0, 0);


	bool quit = false;
	SDL_Event e;
	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			gWindow.handleEvent(e);
		}

		if (!gWindow.isMinimized()) {
			const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
			if (currentKeyStates[SDL_SCANCODE_Q]) {
				foregroundAlpha = min(255, foregroundAlpha + 32);
			}
			else if (currentKeyStates[SDL_SCANCODE_A]) {
				foregroundAlpha = max(0, foregroundAlpha - 32);
			}


			character.step(currentKeyStates);

			// Updates the camera to focus on the main character
			camX = character.getX() - (SCREEN_WIDTH / 2);
			camY = character.getY() - (SCREEN_HEIGHT / 2);

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


			//Clear screen
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
			SDL_RenderClear(gRenderer);

			//gFooTexture.render(240, 190);
			gSpriteSheetTexture.render(0 - camX, 0 - camY, &gSpriteClips[0]);
			gSpriteSheetTexture.render(SCREEN_WIDTH - gSpriteClips[1].w - camX, 0 - camY, &gSpriteClips[1]);
			gSpriteSheetTexture.render(0 - camX, SCREEN_HEIGHT - gSpriteClips[2].h - camY, &gSpriteClips[2]);
			gSpriteSheetTexture.render(SCREEN_WIDTH - gSpriteClips[3].w - camX, SCREEN_HEIGHT - gSpriteClips[3].h - camY, &gSpriteClips[3]);
			//gTextBox.Render();


			gBackgroundTexture.setAlpha(foregroundAlpha);
			gBackgroundTexture.render(0, 0);

			character.render();
			screenBarrierR.render();
			screenBarrierU.render();

			//Update screen
			SDL_RenderPresent(gRenderer);
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
