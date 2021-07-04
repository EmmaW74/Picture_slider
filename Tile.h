#ifndef TILE_H
#define TILE_H
#include "SDL.h"
#include "Defaults.h"
class Tile
{
private:
	SDL_Rect* source_rect; // image on tile, once assigned stays the same throughout the game
	const Defaults* game_defaults;
	int target_position; 
	bool blank;
	int current_position;
	SDL_Rect* destination_rect; // current position on screen, moves during the game
public:
	Tile(SDL_Rect* source_rect, SDL_Rect* dest_rect, int pos);
	void get_tile(SDL_Renderer* gameRenderer, SDL_Texture* imagetexture);
	int get_target_pos() const;
	void update_source_rect(int x, int y, int w, int h);
	void update_dest_rect(int x, int y, int w, int h);
	void update_source_rectangle(SDL_Rect* newRect);
	SDL_Rect* get_source_rect() const;
	SDL_Rect* get_dest_rect() const;
	int get_current_pos() const;
	void update_target_pos(int newpos);
	void update_current_pos(int newpos);
	void update_blank();
	bool get_blank();
};

#endif

