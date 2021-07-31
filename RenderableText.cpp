#include "RenderableText.h"
#include "SDL_ttf.h"
#include "gameWindow.h"

RenderableText::RenderableText(int y, std::string font, std::string text, int size, std::shared_ptr<Defaults> game_defaults):
	y{ y }, text{ text }, font{ font }, size{ size }, game_defaults{ game_defaults }{
	colour_red = game_defaults->get_main_colour_red();
	colour_blue = game_defaults->get_main_colour_blue();
	colour_green = game_defaults->get_main_colour_green();

	TTF_Init();
	TTF_Font* tempFont = TTF_OpenFont(font.c_str(), size); //this opens a font style and sets a size
	SDL_Color tempColor = { colour_red, colour_green, colour_blue };
	text_surface = TTF_RenderText_Solid(tempFont, text.c_str(), tempColor); //Create surface first
	x = (game_defaults->get_screen_width() - text_surface->w) / 2;
}


void RenderableText::render_object(SDL_Renderer* myRenderer) {
	//creates a texture for the text and copies to myRenderer ready to publish
	
	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(myRenderer, text_surface); //Convert to texture

	SDL_Rect Message_rect{x,y,text_surface->w,text_surface->h};
	SDL_RenderCopy(myRenderer, text_texture, NULL, &Message_rect);

	//SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(text_texture);
}

void RenderableText::render_object_left(std::shared_ptr<GameWindow> game_window, signed int adjust){
	//Object slides onto screen from left
	SDL_Rect rect;
	rect.y = y;
	rect.w = text_surface->w;
	rect.h = text_surface->h;

	for (x = 0; x < ((game_defaults->get_screen_width() - text_surface->w) / 2)+adjust; x++) {
		//game_window->fill_background();

		rect.x = x;
		fill_rect(&rect, game_window->get_myRenderer(), game_defaults);
		render_object(game_window->get_myRenderer());
		game_window->publishTexture();
		SDL_Delay(5);
		rect.x = x;
		fill_rect(&rect, game_window->get_myRenderer(), game_defaults); 
	}
	render_object(game_window->get_myRenderer());
	//Add intro text??
}



void RenderableText::render_object_right (std::shared_ptr<GameWindow> game_window) {
	//Object slides onto screen from right
	SDL_Rect rect;
	rect.y = y;
	rect.w = text_surface->w;
	rect.h = text_surface->h;
	for (x = game_defaults->get_screen_width(); x > (game_defaults->get_screen_width() - text_surface->w) / 2; x--) {
		//game_window->fill_background();
		rect.x = x;
		fill_rect(&rect,game_window->get_myRenderer(),game_defaults);
		render_object(game_window->get_myRenderer());
		game_window->publishTexture();
		SDL_Delay(5);	
	}
	render_object(game_window->get_myRenderer());
}

void RenderableText::fill_rect(SDL_Rect* rectangle, SDL_Renderer* renderer, std::shared_ptr<Defaults> gameDefaults) {
	//Fill rectangle with background colour
	
	SDL_SetRenderDrawColor(renderer, gameDefaults->get_intro_background_colour_red(), gameDefaults->get_intro_background_colour_blue(), gameDefaults->get_intro_background_colour_green(), 0xff);
	SDL_RenderFillRect(renderer, rectangle);
	
}

RenderableText::~RenderableText() {
	SDL_FreeSurface(text_surface);
	TTF_Quit();
}