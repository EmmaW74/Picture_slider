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
	std::shared_ptr<Defaults> game_defaults;
	std::shared_ptr<GameWindow> game_window;
	
public:
	Intro(std::shared_ptr<Defaults> game_defaults, std::shared_ptr<GameWindow> window);
	void run_intro();
	void render_title();
	int choose_pic();
	void render_intro_text();
	void render_choose_pic_text();
	void render_grid();
	void renderText(SDL_Surface* surfaceMessage, int y);
	void update_selection(Direction direction);
	void highlight_pic(int pos);
	void display_pics();
	SDL_Texture* upload_pic(const char* pic_file);
	
};

#endif


