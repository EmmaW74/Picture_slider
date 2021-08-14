#include "Tile.h"
Tile::Tile(SDL_Rect* sourceRect, SDL_Rect* dest_rect, int pos):
	targetPosition{ pos }, currentPosition{ pos }, sourceRect{sourceRect}, destinationRect{ dest_rect } {
	blank = false;
}
	
void Tile::getTile(SDL_Renderer* gameRenderer, SDL_Texture* imagetexture) const {
	//Copy tile image to current location on window 
	SDL_RenderCopy(gameRenderer,imagetexture,sourceRect,destinationRect);
}

int Tile::getTargetPos() const {
	return targetPosition;
}

SDL_Rect* Tile::getSourceRect() const {
	return sourceRect;
}
SDL_Rect* Tile::getDestRect() const{
	return destinationRect;
}

void Tile::updateBlank() {
	blank = !blank;
}

bool Tile::getBlank() const {
	return blank;
}

void Tile::updateDestRect(int x, int y, int w, int h) {
	destinationRect->w = w;
	destinationRect->h = h;
	destinationRect->x = x;
	destinationRect->y = y;
}

void Tile::updateSourceRect(SDL_Rect* newRect) {
	sourceRect->x = newRect->x;
	sourceRect->y = newRect->y;
	sourceRect->w = newRect->w;
	sourceRect->h = newRect->h;
}

void Tile::updateTargetPos(int newpos) {
	targetPosition = newpos;
}

void Tile::updateCurrentPos(int newpos) {
	currentPosition = newpos;
}

int Tile::getCurrentPos() const {
	return currentPosition;
}