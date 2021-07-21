#include "Intro.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_render.h"
//#include "TileManager.h"
#include <sstream>
#include <iostream>


Intro::Intro(std::shared_ptr<Defaults> game_defaults, std::shared_ptr<GameWindow> window) :
	game_defaults{ game_defaults }, game_window{ window } {
	
}

void Intro::run_intro() {
	fill_background();
	render_intro_text();
}


void Intro::fill_background() {
	//Fill renderer with background colour
	SDL_Rect* temp = new SDL_Rect{ 0,0,game_defaults->get_screen_width(),game_defaults->get_screen_height()};
	SDL_SetRenderDrawColor(game_window->get_myRenderer(), game_defaults->get_intro_background_colour_red(), game_defaults->get_intro_background_colour_blue(), game_defaults->get_intro_background_colour_green(), 0xff);
	SDL_RenderFillRect(game_window->get_myRenderer(), temp);
	delete temp;
	game_window->publishTexture();
}

void Intro::render_intro_text() {
	//Add title and intro text to screen
	std::istringstream iss{ game_defaults->get_game_name() };
	std::string line1{};
	std::string line2{};
	iss >> line1 >> line2;

	//open font and set font colour
	TTF_Init();
	TTF_Font* font = TTF_OpenFont(game_defaults->get_intro_font().c_str(), 100); 
	SDL_Color color = { game_defaults->get_main_colour_red(), game_defaults->get_main_colour_green(), game_defaults->get_main_colour_blue() };

	//Move first part of title onto screen from left
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, line1.c_str(), color);
	SDL_Texture* textureMessage = SDL_CreateTextureFromSurface(game_window->get_myRenderer(), surfaceMessage);
	int y = game_defaults->get_screen_height() / 4;
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
	for (int x = 0; x < (game_defaults->get_screen_width() - surfaceMessage->w) / 2; x++) {
		render_rect(rect, surfaceMessage, textureMessage, x, y);
		game_window->publishTexture();
		SDL_Delay(5);
	}
	
	//Move second part of title onto screen from left
	surfaceMessage = TTF_RenderText_Solid(font, line2.c_str(), color); 
	textureMessage = SDL_CreateTextureFromSurface(game_window->get_myRenderer(), surfaceMessage);
	y = 4+(game_defaults->get_screen_height() / 5)*2;
	for (int x = game_defaults->get_screen_width(); x > ((game_defaults->get_screen_width() - surfaceMessage->w) / 2)+3; x--) {
		render_rect(rect, surfaceMessage, textureMessage, x, y);
		game_window->publishTexture();
		SDL_Delay(3);
	}

	//Add intro text below game title
	SDL_Delay(300);
	font = TTF_OpenFont(game_defaults->get_intro_font().c_str(), 30);
	surfaceMessage = TTF_RenderText_Solid(font, game_defaults->get_game_intro().c_str(), color);
	textureMessage = SDL_CreateTextureFromSurface(game_window->get_myRenderer(), surfaceMessage);
	y = (game_defaults->get_screen_height() / 4) * 3;
	int x = (game_defaults->get_screen_width() - surfaceMessage->w) / 2;
	render_rect(rect, surfaceMessage,textureMessage,x , y);
	game_window->publishTexture();

	//free surface and quit TTF
	SDL_FreeSurface(surfaceMessage);
	TTF_Quit();
}

void Intro::render_rect(SDL_Rect rect, SDL_Surface* surface, SDL_Texture* texture, int x, int y) {
	//Fills rect with background colour then renders texture at x,y
	rect.x = x;
	rect.y = y;
	rect.w = surface->w;
	rect.h = surface->h;
	SDL_Rect rect2 = rect;
	rect2.h = rect.h+2; 
	rect2.y = y+1; 
	rect2.x = x;
	rect2.w = rect.w; 
	SDL_SetRenderDrawColor(game_window->get_myRenderer(), game_defaults->get_intro_background_colour_red(), game_defaults->get_intro_background_colour_blue(), game_defaults->get_intro_background_colour_green(), 0xff);
	SDL_RenderFillRect(game_window->get_myRenderer(), &rect2);
	SDL_RenderCopy(game_window->get_myRenderer(), texture, NULL, &rect);
}

SDL_Texture* Intro::upload_pic(const char* pic_file) {
	SDL_Surface* tempSurface = IMG_Load(pic_file);
	if (tempSurface == NULL)
	{
		std::cout << "upload_pic: Unable to load image" << SDL_GetError() << std::endl;
	}
	else {

		SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(game_window->get_myRenderer(), tempSurface);
		if (tempTexture == NULL)
		{
			std::cout << "RenderableImage: Unable to create texture" << std::endl;
		}
		else
		{
			SDL_FreeSurface(tempSurface);
			return tempTexture;
		}
	}
}

	void Intro::display_pics() {
		//Displays 4 pics on screen ready to choose
		fill_background();
		SDL_Rect temp{};
		temp.w = (game_defaults->get_screen_width() / 10) * 2;
		temp.h = (game_defaults->get_screen_width() / 10) * 2;
		SDL_Texture* tempTexture;

		int pic = 0;
		for (int x = 2; x < 8; x+=4) {
			for (int y = 2; y < 8; y+=4) {
				tempTexture = upload_pic(game_defaults->get_gamePicture(pic));
				temp.x = ((game_defaults->get_screen_width() / 10) * x);
				temp.y = ((game_defaults->get_screen_width() / 10) * y);
				SDL_RenderCopy(game_window->get_myRenderer(), tempTexture, NULL, &temp);
				pic++;
				game_window->publishTexture();
			}
		}
	}

	void Intro::update_selection(Direction direction){
		//Use arrows to change pic selection and return current position
		if (direction == Direction::LEFT){
			if (game_defaults->get_current_pic() == 0) {
				game_defaults->update_current_pic(3);
			}
			else {
				int temp = game_defaults->get_current_pic();
				temp--;
				game_defaults->update_current_pic(temp);
			}
			//Redraw tiles with selection moved
		}
		else if (direction == Direction::RIGHT) {
			if (game_defaults->get_current_pic() == 3) {
				game_defaults->update_current_pic(0);
			}
			else {
				int temp = game_defaults->get_current_pic();
				temp++;
				game_defaults->update_current_pic(temp);
			}
			
	
			//Redraw tiles with selection moved
		}
		//need to store current selection rect and update as the selection moves
		//also how to deal with up down left right???

		//UP  
		

	//display rect around first pic
		//On arrow press move rect up, down, left or right and update current selection value
		//On Enter, pass current selection to game controller/tile manager? to use that for the game
		//
		game_window->publishTexture();
	}
/*
- render background
- Display 4 pics on screen
- Rectangle around selected pic
- Move selection left and right (pic objects with file, surface, texture, selected bool)
- Press space to select - start game with whichever pic has selection true

*/




