#ifndef TILEMANAGER_H
#define TILEMANAGER_H
#include <string>
#include "SDL.h"
#include "Defaults.h"
#include "gameWindow.h"
#include <memory>
#include <deque>
#include "Tile.h"

enum class Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class TileManager
{
private:
	std::shared_ptr<Defaults> game_defaults;
	std::shared_ptr<GameWindow> game_window;
	std::deque<Tile> tile_list; //deque of tiles
	std::deque<std::pair<int, SDL_Rect*>> start_position_list;
	SDL_Texture* tile_texture;
	int blank_position; //current blank tile position

public:
	TileManager(std::shared_ptr<Defaults> game_defaults, std::shared_ptr<GameWindow> game_window);
	void create_tile_texture();
	void set_rect(SDL_Rect* rect, int pos);
	void create_tile_list();
	void shuffle_tile_list();
	void move_tile(Direction move);
	void swap_tiles(Tile* blank, Tile* pic);

	void draw_tiles();
	void update_blank_pos();
	bool check_solved();


};

#endif