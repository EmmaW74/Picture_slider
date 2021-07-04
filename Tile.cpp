#include "Tile.h"
Tile::Tile(SDL_Rect* source_rect, SDL_Rect* dest_rect, int pos):
	target_position{ pos }, current_position{ pos }, source_rect{source_rect}, destination_rect{ dest_rect } {
	blank = false;
}
	
void Tile::get_tile(SDL_Renderer* gameRenderer, SDL_Texture* imagetexture) {
	//Copy tile image to current location on window 
	SDL_RenderCopy(gameRenderer,imagetexture,source_rect,destination_rect);
}

int Tile::get_target_pos() const {
	return target_position;
}

SDL_Rect* Tile::get_source_rect() const {
	return source_rect;
}
SDL_Rect* Tile::get_dest_rect() const{
	return destination_rect;
}

void Tile::update_blank() {
	blank = !blank;
}

bool Tile::get_blank() {
	return blank;
}

void Tile::update_dest_rect(int x, int y, int w, int h) {
	destination_rect->w = w;
	destination_rect->h = h;
	destination_rect->x = x;
	destination_rect->y = y;
}

void Tile::update_source_rectangle(SDL_Rect* newRect) {
	source_rect->x = newRect->x;
	source_rect->y = newRect->y;
	source_rect->w = newRect->w;
	source_rect->h = newRect->h;
}

void Tile::update_target_pos(int newpos) {
	target_position = newpos;
}

void Tile::update_current_pos(int newpos) {
	current_position = newpos;
}

int Tile::get_current_pos() const {
	return current_position;
}