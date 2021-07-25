#ifndef INTRO_H
#define INTRO_H
#include "SDL.h"
#include "Defaults.h"
#include "IRenderableText.h"
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
	int choose_pic();
	void fill_background();
	void render_intro_text();
	void render_choose_pic_text();
	void render_grid();
	void renderText(SDL_Surface* surfaceMessage, int y);
	void update_selection(Direction direction);
	void render_rect(SDL_Rect rect, SDL_Surface* surface, SDL_Texture* texture, int x, int y);
	void highlight_pic(int pos);
	void display_pics();
	SDL_Texture* upload_pic(const char* pic_file);
	
};

#endif
//When called this function displays welcome screen (game name, press enter to start, drop onto page as tiles)
//Build texture based on block and text then create tiles and drop them on the screen row by row

