#ifndef TILE_H
#define TILE_H
#include "SDL.h"
#include "Defaults.h"
class Tile
	//represents the individual tiles on the board
{
private:
	SDL_Rect* sourceRect; // image on tile, once assigned stays the same throughout the game
	const Defaults* gameDefaults;
	int targetPosition; 
	bool blank;
	int currentPosition;
	SDL_Rect* destinationRect; // current position on screen, moves during the game

public:
	Tile(SDL_Rect* sourceRect, SDL_Rect* dest_rect, int pos);
	void update_sourceRect(int x, int y, int w, int h);
	void updateDestRect(int x, int y, int w, int h);
	void updateSourceRect(SDL_Rect* newRect);
	void updateTargetPos(int newpos);
	void updateCurrentPos(int newpos);
	void updateBlank();
	

	//gets
	void getTile(SDL_Renderer* gameRenderer, SDL_Texture* imagetexture) const;
	int getTargetPos() const;
	SDL_Rect* getSourceRect() const;
	SDL_Rect* getDestRect() const;
	int getCurrentPos() const;
	bool getBlank() const;
};

#endif

