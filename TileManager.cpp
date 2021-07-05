#include "TileManager.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include <algorithm>
#include "gameWindow.h"
#include <random>

TileManager::TileManager(std::shared_ptr<Defaults> game_defaults, std::shared_ptr<GameWindow> game_window):
	game_defaults{ game_defaults }, game_window{ game_window }{
	create_tile_texture();
	//set_blank_pos();
	
}
void TileManager::create_tile_texture() {
	//loads image and creates a texture of the image
	SDL_Surface* tempSurface = IMG_Load(game_defaults->get_game_picture());
	if (tempSurface == NULL)
	{
		std::cout << "RenderableImage: Unable to load image" << SDL_GetError() << std::endl;
	}
	else {
		//Color key image
		SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0xFF, 0xFF, 0xFF));

		//Create texture from surface
		
		tile_texture = SDL_CreateTextureFromSurface(game_window->get_myRenderer(), tempSurface) ;
		//SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(game_window->get_myRenderer(), tempSurface);
		if (tile_texture == NULL)
		{
			std::cout << "RenderableImage: Unable to create texture" << std::endl;
		}
		else
		{
			SDL_FreeSurface(tempSurface);
		}
	}
}

void TileManager::set_rect(SDL_Rect* rect, int pos) {
	//calculate rect position based on pos and update rect x,y,w,h

	rect->w = (game_defaults->get_screen_width() / game_defaults->get_no_across());
	rect->h = (game_defaults->get_screen_height() - game_defaults->get_banner_height()) / game_defaults->get_no_down();
	rect->x = ((pos) % game_defaults->get_no_across()) * rect->w;
	rect->y = (((pos) / game_defaults->get_no_across()) * rect->h) + game_defaults->get_banner_height();
	
}

void TileManager::create_tile_list() {
	//Fill deque with tile objects
	int no_of_tiles = (game_defaults->get_no_across() * game_defaults->get_no_down());
	
	for (int x = 0; x < no_of_tiles; x++) {
		SDL_Rect* tempSourceRect = new SDL_Rect{ 0,0,0 };
		SDL_Rect* tempDestRect = new SDL_Rect{ 0,0,0 };
		set_rect(tempSourceRect, x);
		set_rect(tempDestRect, x);
		std::shared_ptr<Tile> tempTile = std::make_shared<Tile>(tempSourceRect,tempDestRect,x);
		tile_list.push_back(*tempTile); 
	}
	tile_list.at(no_of_tiles - 1).update_blank();
	
}

void TileManager::swap_tiles(Tile* blank, Tile* pic) {
	//Swaps the target position and source rect of the parameter tiles

	SDL_Rect tempBlankSourceRect = *blank->get_source_rect();
	int tempBlankTargetPos = blank->get_target_pos();

	blank->update_target_pos(pic->get_target_pos());
	blank->update_source_rectangle(pic->get_source_rect());

	pic->update_target_pos(tempBlankTargetPos);
	pic->update_source_rectangle(&tempBlankSourceRect);

	Tile* temp_move = blank;
	blank = pic;
	pic = temp_move;

	blank->update_blank();
	pic->update_blank();
	blank_position = blank->get_current_pos();

	//check_solved();
}

void TileManager::move_tile(Direction move) {
	//Calls function to swap tiles based on arrow direction
	if (move == Direction::DOWN && blank_position >= game_defaults->get_no_across()) {
		int temp_blank = blank_position;
		int temp_pic = blank_position - game_defaults->get_no_across();
		swap_tiles(&tile_list.at(temp_blank), &tile_list.at(temp_pic));
	}
	
	else if (move == Direction::UP && blank_position < (game_defaults->get_no_across()* (game_defaults->get_no_down()-1))) {
		int temp_blank = blank_position;
		int temp_pic = blank_position + game_defaults->get_no_across();
		swap_tiles(&tile_list.at(temp_blank), &tile_list.at(temp_pic));
	} 

	else if (move == Direction::LEFT && ((blank_position+1) % game_defaults->get_no_across())!= 0) {
		int temp_blank = blank_position;
		int temp_pic = blank_position + 1;
		swap_tiles(&tile_list.at(temp_blank), &tile_list.at(temp_pic));
	}

	else if (move == Direction::RIGHT && ((blank_position + 1) % game_defaults->get_no_across()) != 1) {
		int temp_blank = blank_position;
		int temp_pic = blank_position - 1;
		swap_tiles(&tile_list.at(temp_blank), &tile_list.at(temp_pic));
	}

	SDL_RenderClear(game_window->get_myRenderer());
	draw_tiles();
}

void TileManager::update_blank_pos() {
	//Records current position of blank tile
	auto it = tile_list.begin();
	if (it!=tile_list.end() && it->get_blank()) {
		blank_position = it->get_current_pos();
		it++;
	}
}

void TileManager::shuffle_tile_list() {
	//Shuffles tiles in deque, updates current position and destination rect for each tile, records starting blank position
	shuffle(tile_list.begin(), tile_list.end(), std::default_random_engine(std::random_device()()));
	int no_of_tiles = (game_defaults->get_no_across() * game_defaults->get_no_down());
	int pos = 0;
	for (int x = 0; x < no_of_tiles; x++) {
		SDL_Rect* tempRect = new SDL_Rect{ 0,0,0 };
		set_rect(tempRect, pos);
		tile_list.at(pos).update_dest_rect(tempRect->x, tempRect->y, tempRect->w, tempRect->h);
		tile_list.at(pos).update_current_pos(pos);
		if (tile_list.at(pos).get_blank()) {
			blank_position = pos;
		}
		pos++;
	}
	//update_blank_pos(); WHY IS IT SKIPPING THIS??
}

void TileManager::draw_tiles() {
	//Draws source rect in dest rect for each tile not flagged as blank. For blank tile it draws a blank square.
	auto it = tile_list.begin();
	while (it != tile_list.end()) {
		if (it->get_blank()) {
			SDL_SetRenderDrawColor(game_window->get_myRenderer(), 0x00, 0x00, 0x00, 0x00);
			SDL_RenderFillRect(game_window->get_myRenderer(), it->get_dest_rect());
		}
		else {
			SDL_RenderCopy(game_window->get_myRenderer(), tile_texture, it->get_source_rect(), it->get_dest_rect());
		}
		it++;
	}
	game_window->publishTexture();
	
}
bool TileManager::check_solved() {
	//Checks if each tile is currently in the target position
	auto it = tile_list.begin();
	
	while (it != tile_list.end()) {
		if (it->get_current_pos() != it->get_target_pos()) {
			std::cout << "Not solved" << std::endl;
			return false;
		}
		it++;
	}
	std::cout << "Solved" << std::endl;
	return true;
}
