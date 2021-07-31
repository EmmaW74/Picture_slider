#include "Intro.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_render.h"
#include <sstream>
#include <iostream>


Intro::Intro(std::shared_ptr<Defaults> game_defaults, std::shared_ptr<GameWindow> window) :
	game_defaults{ game_defaults }, game_window{ window } {
}

void Intro::run_intro() {
	//calls methods to display intro screen
	game_window->fill_background();
	render_title();
	render_intro_text();
}

void Intro::render_title() {
	//Add title and intro text to renderer and publish to screen
	std::istringstream iss{ game_defaults->get_game_name() };
	std::string line1{};
	std::string line2{};
	iss >> line1 >> line2;

	int y = (game_defaults->get_screen_height() / 5);
	int size = 100;
	RenderableText title_line1{ y,game_defaults->get_intro_font(),line1,size,game_defaults };
	title_line1.render_object_left(game_window,-5);
	
	y = (game_defaults->get_screen_height() / 5) + size;
	RenderableText title_line2{ y,game_defaults->get_intro_font(),line2,size,game_defaults };
	title_line2.render_object_right(game_window);

	
}

void Intro::render_choose_pic_text() {
	int y = game_defaults->get_screen_height() / 10;
	int size = 26;
	RenderableText choose_pic{ y,game_defaults->get_intro_font(),game_defaults->get_choose_pic_text(),size,game_defaults };
	choose_pic.render_object(game_window->get_myRenderer());
	game_window->publishTexture();
}

void Intro::render_intro_text() {
	int y = (game_defaults->get_screen_height() / 10)*7;
	int size = 30;
	RenderableText choose_pic{ y,game_defaults->get_intro_font(),game_defaults->get_game_intro(),size,game_defaults };
	choose_pic.render_object(game_window->get_myRenderer());
	game_window->publishTexture();
}

SDL_Texture* Intro::upload_pic(const char* pic_file) {
	//Uploads picture file and returns as a texture
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
		game_window->fill_background();
		SDL_Rect temp{};
		temp.w = (game_defaults->get_screen_width() / 10) * 2;
		temp.h = (game_defaults->get_screen_width() / 10) * 2;
		SDL_Texture* tempTexture;

		int pic = 0;
		for (int y = 2; y < 8; y += 4) {
			for (int x = 2; x < 8; x+=4) {
				tempTexture = upload_pic(game_defaults->get_gamePicture(pic));
				temp.x = ((game_defaults->get_screen_width() / 10) * x);
				temp.y = ((game_defaults->get_screen_width() / 10) * y);
				SDL_RenderCopy(game_window->get_myRenderer(), tempTexture, NULL, &temp);
				pic++;
			}
		}
		render_choose_pic_text();
		
	}
	void Intro::highlight_pic(int pos) {
		//Draws calls function to draw rect around selected picture
		game_window->fill_background();
		display_pics();

		int pic_dimension = (game_defaults->get_screen_width() / 10) * 2;
		
		SDL_Rect outlineRect{};
		outlineRect.w = pic_dimension;
		outlineRect.h = pic_dimension;
		outlineRect.x = (pic_dimension + ((pos % 2) * (2 * pic_dimension)));
		outlineRect.y = (pic_dimension + ((pos / 2) * (2 * pic_dimension)));

		game_window->draw_rectangle(outlineRect, 6, game_defaults);
		game_window->publishTexture();
	}

	void Intro::update_selection(Direction direction){
		//Update default current picture and move highlight on screen based on direction argument
		
		if (direction == Direction::LEFT){
			if (game_defaults->get_current_pic() == 0) {
				game_defaults->update_current_pic(3);
				highlight_pic(3);
			}
			else {
				int temp = game_defaults->get_current_pic();
				temp--;
				game_defaults->update_current_pic(temp);
				highlight_pic(temp);
			}
		}
		else if (direction == Direction::RIGHT) {
		
			if (game_defaults->get_current_pic() == 3) {
				game_defaults->update_current_pic(0);
				highlight_pic(0);
			}
			else {
				int temp = game_defaults->get_current_pic();
				temp++;
				game_defaults->update_current_pic(temp);
				highlight_pic(temp);
			}
		}
	}





