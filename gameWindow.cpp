#include "gameWindow.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "SDL_ttf.h"

GameWindow::GameWindow(std::shared_ptr<Defaults> game_Defaults) :
	gameDefaults{ game_Defaults } {

	//Initialisation flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		//Create window
		myAppWindow = SDL_CreateWindow("Picture slider game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gameDefaults->get_screen_width(), gameDefaults->get_screen_height(), SDL_WINDOW_SHOWN);
		if (myAppWindow == NULL)
		{
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			//Create renderer
			myRenderer = SDL_CreateRenderer(myAppWindow, -1, SDL_RENDERER_ACCELERATED);
			if (myRenderer == NULL)
			{
				std::cout << "Renderer could not be created!" << SDL_GetError();
				success = false;
			}
		}
	}
}

	SDL_Renderer* GameWindow::get_myRenderer() const {
		return myRenderer; 
	}


void GameWindow::drawFrame() {
	// Draws current state of puzzle
	
	//Do something here
	publishTexture();
}

void GameWindow::publishTexture() {
	SDL_RenderPresent(myRenderer);
}


GameWindow::~GameWindow() {
	//Free loaded images
	if (myTexture != NULL) {
		SDL_DestroyTexture(myTexture);
		myTexture = NULL;
	}


	//Destroy window    
	SDL_DestroyRenderer(myRenderer);
	SDL_DestroyWindow(myAppWindow);
	myAppWindow = NULL;
	myRenderer = NULL;


	//Quit SDL subsystems
	//IMG_Quit();
	//TTF_Quit();
	SDL_Quit();

}