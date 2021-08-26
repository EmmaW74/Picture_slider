#include "gameWindow.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "SDL_ttf.h"

GameWindow::GameWindow(std::shared_ptr<Defaults> gameDefaults) :
	gameDefaults{ gameDefaults } {

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
		myAppWindow = SDL_CreateWindow("Picture slider game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gameDefaults->getScreenWidth(), gameDefaults->getScreenHeight(), SDL_WINDOW_SHOWN);
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

SDL_Renderer* GameWindow::getMyRenderer() const {
		return myRenderer; 
}

void GameWindow::createTileTexture() {
	//loads image and creates a texture of the image
	SDL_Surface* tempSurface = IMG_Load(gameDefaults->getGamePicture(gameDefaults->getCurrentPic()));
	if (tempSurface == NULL)
	{
		std::cout << "RenderableImage: Unable to load image" << SDL_GetError() << std::endl;

	}
	else {

		SDL_Texture* tileTexture = SDL_CreateTextureFromSurface(getMyRenderer(), tempSurface);

		if (tileTexture == NULL)
		{
			std::cout << "RenderableImage: Unable to create texture" << std::endl;
		}
		else
		{
			SDL_FreeSurface(tempSurface);
		}
		myTexture = tileTexture;
	}
}


void GameWindow::publishTexture() const {
	SDL_RenderPresent(myRenderer);
}

SDL_Texture* GameWindow::getMyTexture() {
	return myTexture;
}

void GameWindow::fillBackground() {
	//Fill renderer with background colour
	SDL_Rect* temp = new SDL_Rect{ 0,0,gameDefaults->getScreenWidth(),gameDefaults->getScreenHeight() };
	SDL_SetRenderDrawColor(getMyRenderer(), gameDefaults->getIntroBackgroundColourRed(), gameDefaults->getIntroBackgroundColourBlue(), gameDefaults->getIntroBackgroundColourGreen(), 0xff);
	SDL_RenderFillRect(getMyRenderer(), temp);
	delete temp;
}

void GameWindow::drawRectangle(SDL_Rect rect, const int borderSize, std::shared_ptr<Defaults>gameDefaults) {
	
	int widthAdj = 0;
	int posAdj = 0;
	for (int x = 0; x < borderSize; x++) {
		rect.w = rect.w + widthAdj;
		rect.h = rect.h + widthAdj;
		rect.x = rect.x - posAdj;
		rect.y = rect.y - posAdj;

		SDL_SetRenderDrawColor(getMyRenderer(), gameDefaults->getMainColourRed(), gameDefaults->getMainColourGreen(), gameDefaults->getMainColourBlue(), 0xff);
		SDL_RenderDrawRect(getMyRenderer(), &rect);
		widthAdj = 2;
		posAdj = 1;
	}
}

void GameWindow::drawReferencePic() {
	//Draws pic on screen for reference
	SDL_Rect outlineRect{};
	outlineRect.w = gameDefaults->getGridWidth()/3;
	outlineRect.h = gameDefaults->getGridHeight()/3;
	outlineRect.x = gameDefaults->getScreenWidth() - gameDefaults->getLeftMargin() - outlineRect.w;
	outlineRect.y = gameDefaults->getBannerHeight();


	SDL_RenderCopy(getMyRenderer(), myTexture, NULL, &outlineRect);
	drawRectangle(outlineRect, 3, gameDefaults);
	//publishTexture();

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