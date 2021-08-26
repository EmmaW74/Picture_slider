#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include "SDL.h"
#include "SDL_image.h"
#include "Defaults.h"
#include<memory>

class GameWindow
{
	//This class handles window creation and rendering
private:

	SDL_Window* myAppWindow = NULL;
	SDL_Renderer* myRenderer = NULL;
	SDL_Texture* myTexture = NULL;
	std::shared_ptr<Defaults> gameDefaults; 


public:

	GameWindow(std::shared_ptr<Defaults> gameDefaults);
	void publishTexture() const;
	void createTileTexture();
	SDL_Renderer* getMyRenderer() const;
	void fillBackground();
	void drawRectangle(SDL_Rect rect, const int borderSize, std::shared_ptr<Defaults>gameDefaults);
	void drawReferencePic();
	SDL_Texture* getMyTexture();
	~GameWindow();
};

#endif


