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

void GameWindow::publishTexture() {
	SDL_RenderPresent(myRenderer);
}

void GameWindow::fill_background() {
	//Fill renderer with background colour
	SDL_Rect* temp = new SDL_Rect{ 0,0,gameDefaults->get_screen_width(),gameDefaults->get_screen_height() };
	SDL_SetRenderDrawColor(get_myRenderer(), gameDefaults->get_intro_background_colour_red(), gameDefaults->get_intro_background_colour_blue(), gameDefaults->get_intro_background_colour_green(), 0xff);
	SDL_RenderFillRect(get_myRenderer(), temp);
	delete temp;
}

void GameWindow::draw_rectangle(SDL_Rect rect, int border_size, std::shared_ptr<Defaults>game_defaults) {
	
	int width_adj = 0;
	int pos_adj = 0;
	for (int x = 0; x < border_size; x++) {
		rect.w = rect.w + width_adj;
		rect.h = rect.h + width_adj;
		rect.x = rect.x - pos_adj;
		rect.y = rect.y - pos_adj;

		SDL_SetRenderDrawColor(get_myRenderer(), game_defaults->get_main_colour_red(), game_defaults->get_main_colour_green(), game_defaults->get_main_colour_blue(), 0xff);
		SDL_RenderDrawRect(get_myRenderer(), &rect);
		width_adj = 2;
		pos_adj = 1;
	}
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