#ifndef INTRO_H
#define INTRO_H
#include "SDL.h"
#include "Defaults.h"
#include "RenderableText.h"
#include "gameWindow.h"
#include "TileManager.h"
#include <string>


class Intro
{
private:
	std::shared_ptr<Defaults> gameDefaults;
	std::shared_ptr<GameWindow> gameWindow;
	
public:
	Intro(std::shared_ptr<Defaults> gameDefaults, std::shared_ptr<GameWindow> window);
	void runIntro();
	void renderTitle();
	int choosePic();
	void renderIntroText();
	void renderChoosePicText();
	void renderGrid();
	void renderText(SDL_Surface* surfaceMessage, int y);
	void updateSelection(Direction direction);
	void highlightPic(int pos);
	void displayPics();
	SDL_Texture* uploadPic(const char* picFile);
	
};

#endif


