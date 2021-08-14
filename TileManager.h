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
	//Creates and shuffles tile list and manages movement of tiles
{
private:
	std::shared_ptr<Defaults> gameDefaults;
	std::shared_ptr<GameWindow> gameWindow;
	std::deque<Tile> tileList; 
	SDL_Texture* tileTexture;
	int blankTilePosition; 


public:
	TileManager(std::shared_ptr<Defaults> gameDefaults, std::shared_ptr<GameWindow> gameWindow);
	void createTileTexture();
	void setRect(SDL_Rect* rect, int pos);
	void createTileList();
	void shuffleTileList();
	void moveTile(Direction move);
	void swapTiles(Tile* blank, Tile* pic);
	void drawTiles();
	void updateBlankPos();
	bool checkSolved();
	int countInversions();
	bool checkSolvable(int gridSize);

};

#endif