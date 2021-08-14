#include "RenderableText.h"
#include "SDL_ttf.h"
#include "gameWindow.h"

RenderableText::RenderableText(int y, std::string font, std::string text, int size, std::shared_ptr<Defaults> gameDefaults, uint8_t colourRed, uint8_t colourGreen, uint8_t colourBlue):
	y{ y }, text{ text }, font{ font }, size{ size }, gameDefaults{ gameDefaults }, colourRed{ colourRed }, colourGreen{ colourGreen }, colourBlue{ colourBlue }{

	TTF_Init();
	TTF_Font* tempFont = TTF_OpenFont(font.c_str(), size); 
	SDL_Color tempColor = { colourRed, colourGreen, colourBlue };
	textSurface = TTF_RenderText_Solid(tempFont, text.c_str(), tempColor); 
	x = (gameDefaults->getScreenWidth() - textSurface->w) / 2;
}

void RenderableText::changeX(int newReferencePoint) {
	//updates the x co-ordinate for the text on screen
	x = ((gameDefaults->getGridWidth() - textSurface->w)/2) + gameDefaults->getLeftMargin();
}

void RenderableText::renderObject(SDL_Renderer* myRenderer) const {
	//creates a texture for the text and copies to myRenderer ready to publish
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(myRenderer, textSurface); 
	SDL_Rect messageRect{x,y,textSurface->w,textSurface->h};
	SDL_RenderCopy(myRenderer, textTexture, NULL, &messageRect);
	SDL_DestroyTexture(textTexture);
}

void RenderableText::renderObjectLeft(std::shared_ptr<GameWindow> gameWindow, signed int adjust) {
	//Object slides onto screen from left
	SDL_Rect rect;
	rect.y = y;
	rect.w = textSurface->w;
	rect.h = textSurface->h;

	for (x = 0; x < ((gameDefaults->getScreenWidth() - textSurface->w) / 2)+adjust; x++) {
		rect.x = x;
		fillRect(&rect, gameWindow->getMyRenderer(), gameDefaults);
		renderObject(gameWindow->getMyRenderer());
		gameWindow->publishTexture();
		SDL_Delay(1);
		rect.x = x;
		fillRect(&rect, gameWindow->getMyRenderer(), gameDefaults); 
	}
	renderObject(gameWindow->getMyRenderer());
}



void RenderableText::renderObjectRight (std::shared_ptr<GameWindow> gameWindow) {
	//Object slides onto screen from right
	SDL_Rect rect;
	rect.y = y;
	rect.w = textSurface->w;
	rect.h = textSurface->h;
	for (x = gameDefaults->getScreenWidth(); x > (gameDefaults->getScreenWidth() - textSurface->w) / 2; x--) {
		rect.x = x;
		fillRect(&rect,gameWindow->getMyRenderer(),gameDefaults);
		renderObject(gameWindow->getMyRenderer());
		gameWindow->publishTexture();
		SDL_Delay(1);	
	}
	renderObject(gameWindow->getMyRenderer());
}

void RenderableText::fillRect(SDL_Rect* rectangle, SDL_Renderer* renderer, std::shared_ptr<Defaults> gameDefaults) const {
	//Fill rectangle with background colour
	SDL_SetRenderDrawColor(renderer, gameDefaults->getIntroBackgroundColourRed(), gameDefaults->getIntroBackgroundColourBlue(), gameDefaults->getIntroBackgroundColourGreen(), 0xff);
	SDL_RenderFillRect(renderer, rectangle);
}

RenderableText::~RenderableText() {
	SDL_FreeSurface(textSurface);
	TTF_Quit();
}