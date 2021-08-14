#ifndef RENDERABLETEXT_H
#define RENDERABLETEXT_H

#include "SDL.h"
#include "Defaults.h"
#include "gameWindow.h"
#include <string>

class RenderableText
{
	// Stores details of a text object and draws on screen
private:

	std::shared_ptr<Defaults> gameDefaults;
	int x;
	int y;
	uint8_t colourRed;
	uint8_t colourBlue;
	uint8_t colourGreen;
	std::string text;
	int size;
	std::string font;
	SDL_Surface* textSurface;
	
public:

	RenderableText(int y, std::string font, std::string text, int size, std::shared_ptr<Defaults> gameDefaults, uint8_t colourRed,uint8_t colourGreen,uint8_t colourBlue);
	void fillRect(SDL_Rect* rectangle, SDL_Renderer* renderer, std::shared_ptr<Defaults> gameDefaults) const;
	void renderObject(SDL_Renderer* myRenderer) const;
	void renderObjectLeft(std::shared_ptr<GameWindow> gameWindow, signed int adjust = 0);
	void renderObjectRight(std::shared_ptr<GameWindow> gameWindow);
	void changeX(int newReferencePoint);
	~RenderableText();
	
};

#endif
