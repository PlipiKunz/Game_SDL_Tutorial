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
#include "utils.h"
#include "EnemyA.h"

//Tutorial: https://lazyfoo.net/tutorials/SDL/index.php

//True Global variable declaractions any file can access by importing globals
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

GameStates GAME_STATE = GameStates::normal;

LWindow gWindow = LWindow();
SDL_Renderer* gRenderer = nullptr;

std::map<int, SDL_Rect> pageRects = {};

Room CURRENT_ROOM = Room();
int ROOM_WIDTH = 0;
int ROOM_HEIGHT = 0;
int ROOM_NUMBER = 0;

int camX = 0;
int camY = 0;

CharacterObject mainCharacter = CharacterObject();


//Local global definitions
TTF_Font* gFont = nullptr;
TextBox gTextBox;


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

bool loadRoom(int room_number) {
	//sets the room number
	ROOM_NUMBER = room_number;

	//the if branch for rooms
	if (room_number == 0) {
		CURRENT_ROOM = Room();
	}

	//updates the room width and heights
	ROOM_WIDTH = CURRENT_ROOM.getRoomWidth();
	ROOM_HEIGHT = CURRENT_ROOM.getRoomHeight();

	//tries to load the room and returns the result
	return CURRENT_ROOM.load();
}

bool loadMedia()
{
	//sets success to be the result of room loading
	bool success = loadRoom(0);

	//Load the textbox
	gFont = TTF_OpenFont("Fonts/lazy.ttf", 28);
	if (gFont == nullptr) {
		printf("Failed to load lazy font! SDL_ttf Error %s\n", TTF_GetError());
		success = false;
	}
	else {
		//sets the font and loads some text into the textbox
		gTextBox.setFont(gFont);
		if (!gTextBox.loadText("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aliquam iaculis quis erat eu hendrerit. Nam eu vulputate ligula, id fermentum tortor. Aliquam molestie ornare fringilla. Quisque posuere sit amet purus a eleifend. Donec dapibus tempor pretium. Nam elementum vulputate ipsum tempus aliquam. Proin laoreet enim sit amet leo mollis convallis ut non elit. Aliquam elementum libero tellus, at pretium purus scelerisque sed.")) {
			printf("Failed to render text texture!\n");
			success = false;
		}
	}
	return success;
}

void close()
{
	CURRENT_ROOM.free();

	//remove the textbox
	gTextBox.free();

	//cleanup font
	TTF_CloseFont(gFont);
	gFont = nullptr;

	//Destroy window    
	gWindow.free();
	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void step(const Uint8* currentKeyStates) {

	if (GAME_STATE == GameStates::normal) {
		CURRENT_ROOM.step(currentKeyStates);
	}
	else if (GAME_STATE == GameStates::text_box) {

	}
}

void render() {
	//Clear screen
	SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(gRenderer);


	if (GAME_STATE == GameStates::normal) {
		CURRENT_ROOM.render();
	}
	else if (GAME_STATE == GameStates::text_box) {
		CURRENT_ROOM.render();
		gTextBox.Render();
	}

	//Update screen
	SDL_RenderPresent(gRenderer);
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

			step(currentKeyStates);
			render();
		}
	}

	//Free resources and close SDL
	close();
	return 0;
}
