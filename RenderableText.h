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

	std::shared_ptr<Defaults> game_defaults;
	int x;
	int y;
	uint8_t colour_red;
	uint8_t colour_blue;
	uint8_t colour_green;
	std::string text;
	int size;
	std::string font;
	SDL_Surface* text_surface;
	//SDL_Texture* text_texture;

	void fill_rect(SDL_Rect* rectangle, SDL_Renderer* renderer, std::shared_ptr<Defaults> gameDefaults);

public:

	RenderableText(int y, std::string font, std::string text, int size, std::shared_ptr<Defaults> game_defaults);
	void render_object(SDL_Renderer* myRenderer);
	void render_object_left(std::shared_ptr<GameWindow> game_window, signed int adjust = 0);
	void render_object_right(std::shared_ptr<GameWindow> game_window);
	~RenderableText();
	//int get_x() const;
	//int get_y() const;
	//std::string get_font() const;
	//std::string get_text() const;
	//void update_text(std::string newtext);

	//uint8_t get_colour_red() const;
	//uint8_t get_colour_blue() const;
	//uint8_t get_colour_green() const;

	//void draw_element(SDL_Renderer* myRenderer);

	

};


#endif
