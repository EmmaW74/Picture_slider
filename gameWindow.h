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
	std::shared_ptr<Defaults> gameDefaults; //Need defaults class created


public:

	GameWindow(std::shared_ptr<Defaults> game_defaults);
	void publishTexture();
	SDL_Renderer* get_myRenderer() const;
	void fill_background();
	~GameWindow();
};

#endif


