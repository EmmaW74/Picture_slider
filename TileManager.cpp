#include "TileManager.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include <algorithm>
#include "gameWindow.h"
#include <random>

TileManager::TileManager(std::shared_ptr<Defaults> gameDefaults, std::shared_ptr<GameWindow> gameWindow):
	gameDefaults{ gameDefaults }, gameWindow{ gameWindow }{
	//createTileTexture();
	
}
void TileManager::createTileTexture() {
	//loads image and creates a texture of the image MOVE TO GAME WINDOW??
	SDL_Surface* tempSurface = IMG_Load(gameDefaults->getGamePicture(gameDefaults->getCurrentPic()));
	if (tempSurface == NULL)
	{
		std::cout << "RenderableImage: Unable to load image" << SDL_GetError() << std::endl;
	}
	else {
		
		tileTexture = SDL_CreateTextureFromSurface(gameWindow->getMyRenderer(), tempSurface) ;
		
		if (tileTexture == NULL)
		{
			std::cout << "RenderableImage: Unable to create texture" << std::endl;
		}
		else
		{
			SDL_FreeSurface(tempSurface);
		}
	}
}

void TileManager::setRect(SDL_Rect* rect, int pos) {
	//calculate rect position based on pos and update rect x,y,w,h
	rect->w = gameDefaults->getGridWidth() / gameDefaults->getNoAcross();
	rect->h = gameDefaults->getGridHeight() / gameDefaults->getNoDown();
	rect->x = (((pos) % gameDefaults->getNoAcross()) * rect->w) + gameDefaults->getLeftMargin();
	rect->y = (((pos) / gameDefaults->getNoAcross()) * rect->h) + gameDefaults->getBannerHeight();
}

void TileManager::createTileList() {
	//Fill deque with tile objects
	int noOfTiles = (gameDefaults->getNoAcross() * gameDefaults->getNoDown());
	for (int x = 0; x < noOfTiles; x++) {
		SDL_Rect* tempSourceRect = new SDL_Rect{ 0,0,0 };
		SDL_Rect* tempDestRect = new SDL_Rect{ 0,0,0 };
		setRect(tempSourceRect, x);
		setRect(tempDestRect, x);
		std::shared_ptr<Tile> tempTile = std::make_shared<Tile>(tempSourceRect,tempDestRect,x);
		tileList.push_back(*tempTile); 
	}
	tileList.at(noOfTiles - 1).updateBlank();

	
}


void TileManager::clearTileList() {
	tileList.clear();
}

void TileManager::swapTiles(Tile* blank, Tile* pic) {
	//Swaps the target position and source rect of the parameter tiles

	SDL_Rect tempBlankSourceRect = *blank->getSourceRect();
	int tempBlankTargetPos = blank->getTargetPos();

	blank->updateTargetPos(pic->getTargetPos());
	blank->updateSourceRect(pic->getSourceRect());

	pic->updateTargetPos(tempBlankTargetPos);
	pic->updateSourceRect(&tempBlankSourceRect);

	Tile* tempMove = blank;
	blank = pic;
	pic = tempMove;

	blank->updateBlank();
	pic->updateBlank();
	blankTilePosition = blank->getCurrentPos();

}

void TileManager::moveTile(Direction move) {
	//Calls function to swap tiles based on arrow direction
	if (move == Direction::DOWN && blankTilePosition >= gameDefaults->getNoAcross()) {
		int tempBlank = blankTilePosition;
		int tempPic = blankTilePosition - gameDefaults->getNoAcross();
		swapTiles(&tileList.at(tempBlank), &tileList.at(tempPic));
	}
	
	else if (move == Direction::UP && blankTilePosition < (gameDefaults->getNoAcross()* (gameDefaults->getNoDown()-1))) {
		int tempBlank = blankTilePosition;
		int tempPic = blankTilePosition + gameDefaults->getNoAcross();
		swapTiles(&tileList.at(tempBlank), &tileList.at(tempPic));
	} 

	else if (move == Direction::LEFT && ((blankTilePosition+1) % gameDefaults->getNoAcross())!= 0) {
		int tempBlank = blankTilePosition;
		int tempPic = blankTilePosition + 1;
		swapTiles(&tileList.at(tempBlank), &tileList.at(tempPic));
	}

	else if (move == Direction::RIGHT && ((blankTilePosition + 1) % gameDefaults->getNoAcross()) != 1) {
		int tempBlank = blankTilePosition;
		int tempPic = blankTilePosition - 1;
		swapTiles(&tileList.at(tempBlank), &tileList.at(tempPic));
	}

	SDL_RenderClear(gameWindow->getMyRenderer());
	gameWindow->fillBackground();
	drawTiles();
}

void TileManager::updateBlankPos() {
	//Records current position of blank tile
	auto it = tileList.begin();
	if (it!=tileList.end() && it->getBlank()) {
		blankTilePosition = it->getCurrentPos();
		it++;
	}
}

void TileManager::shuffleTileList() {
	//Shuffles tiles in deque, updates current position and destination rect for each tile, records starting blank position
	
	do {
		shuffle(tileList.begin(), tileList.end(), std::default_random_engine(std::random_device()()));
		int noOfTiles = (gameDefaults->getNoAcross() * gameDefaults->getNoDown());
		int pos = 0;
		for (int x = 0; x < noOfTiles; x++) {
			SDL_Rect* tempRect = new SDL_Rect{ 0,0,0 };
			setRect(tempRect, pos);
			tileList.at(pos).updateDestRect(tempRect->x, tempRect->y, tempRect->w, tempRect->h);
			tileList.at(pos).updateCurrentPos(pos);
			if (tileList.at(pos).getBlank()) {
				blankTilePosition = pos;
			}
			pos++;
		}
	} while (!checkSolvable(gameDefaults->getNoDown()));
		
	//initial_list = tileList; //Test - copy initial list
	//initial_inversions = countInversions();
}

bool TileManager::checkSolvable(int gridSize) {
	int blankPos = NULL;
	if (gridSize % 2 == 0) {
		//EVEN SIZED GRID
		//First iterate to find current pos of blank tile (blank is true)
		for (auto& i : tileList) {
			if (i.getBlank()) {
				blankPos = i.getCurrentPos();
			}
		}

		if ((blankPos / gameDefaults->getNoDown()) % 2 == 1) {
			//If blank is on odd row from bottom (row n-1, n-3 .... n-n) even inversions is valid
			if (countInversions() % 2 != 0) {
				return false;
			}
			else {
				return true;
			}
		}
		else {
			//if blank is on even row from bottom (row n-1, n-3 .... n-n), odd inversions is valid
			if (countInversions() % 2 == 0) {
				return false;
			}
			else {
				return true;
			}
		}
	} else {

		//ODD SIZED GRID - solvable if even number of inversions
		if (countInversions() %2 != 0) {
			return false;
		}
		else {
			return true;
		}
	}
}


int TileManager::countInversions() {
	//iterate over all pairs and keep a running count of inversions (even no is valid if grid is odd)
	int count = 0;
	for (unsigned int x = 0; x < tileList.size(); x++) {
		for (unsigned int y = x+1; y < tileList.size(); y++) {
			if (!tileList.at(x).getBlank() && (tileList.at(x).getTargetPos() > tileList.at(y).getTargetPos())) {
				count++;
			}
		}
	}
	return count;
}

void TileManager::drawTiles() {
	//Draws source rect in dest rect for each tile not flagged as blank. For blank tile it draws a blank square.
	
	auto it = tileList.begin();
	while (it != tileList.end()) {
		if (it->getBlank()) {
			SDL_SetRenderDrawColor(gameWindow->getMyRenderer(), gameDefaults->getIntroBackgroundColourRed(), gameDefaults->getIntroBackgroundColourBlue(), gameDefaults->getIntroBackgroundColourGreen(),255);
			SDL_RenderFillRect(gameWindow->getMyRenderer(), it->getDestRect());
			
		}
		else {
			SDL_RenderCopy(gameWindow->getMyRenderer(), gameWindow->getMyTexture(), it->getSourceRect(), it->getDestRect());
		}
		it++;
	}
	SDL_Rect outlineRect{};
	outlineRect.w = gameDefaults->getGridWidth();
	outlineRect.h = gameDefaults->getGridHeight();
	outlineRect.x = gameDefaults->getLeftMargin();
	outlineRect.y = gameDefaults->getBannerHeight();

	gameWindow->drawRectangle(outlineRect, 3, gameDefaults);
	gameWindow->drawReferencePic();
	gameWindow->publishTexture();
	
}

bool TileManager::checkSolved() {
	//Checks if each tile is currently in the target position
	auto it = tileList.begin();
	
	while (it != tileList.end()) {
		if (it->getCurrentPos() != it->getTargetPos()) {
			std::cout << "Not solved" << std::endl;
			return false;
		}
		it++;
	}
	std::cout << "Solved" << std::endl;
	return true;
}
