#include "gameController.h"
#include <iostream>

GameController::GameController() {
	gameDefaults = std::make_shared<Defaults>();
	gameWindow = std::make_shared<GameWindow>(gameDefaults);
	gameTiles = std::make_shared<TileManager>(gameDefaults, gameWindow);
	gameIntro = std::make_shared<Intro>(gameDefaults,gameWindow);
	gameIsOver = std::make_shared<gameOver>(gameDefaults, gameWindow);
	started = false;
	running = false;
}

void GameController::updateRunning() {
	running = !running;
}
void GameController::startGame() {
	gameIntro->runIntro();
	SDL_Event e;
	while (!started) {
		if (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT)
				//User requests quit
			{
				if (quitGame()) {
					updateStarted();
				}
				else {
					gameIntro->runIntro();
				}
			}
			else if (e.type == SDL_KEYDOWN) {

				if (e.key.keysym.sym == SDLK_RETURN) {
					updateStarted();
					choosePic();
					
				}
			}
		}
	}
}

void GameController::choosePic() {
	bool picked = false;
	gameIntro->displayPics();
	gameIntro->highlightPic(gameDefaults->getCurrentPic());
	SDL_Event e;
	while (!picked) {
		if (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT)
				//User requests quit
			{
				if (quitGame()) {
					picked = true;
				}
				else {
					gameIntro->displayPics();
					gameIntro->highlightPic(gameDefaults->getCurrentPic());
				}
				
			}
			else if (e.type == SDL_KEYDOWN) {

				if (e.key.keysym.sym == SDLK_LEFT) {
					gameIntro->updateSelection(Direction::LEFT);

				} else if (e.key.keysym.sym == SDLK_RIGHT) {
					gameIntro->updateSelection(Direction::RIGHT);
				}
				else if (e.key.keysym.sym == SDLK_RETURN) {
					picked = true;
					gameWindow->createTileTexture();
					runGame();
				}
			}
		}
	}
}

void GameController::runGame() {
	gameWindow->fillBackground();
	running = true;
	//gameTiles = std::make_shared<TileManager>(gameDefaults, gameWindow);
	gameTiles->createTileList();
	gameTiles->drawTiles();
	SDL_Delay(2000);
	gameTiles->shuffleTileList();
	gameTiles->drawTiles();

	SDL_Event e;
	while (running) {
		if (SDL_PollEvent(&e) != 0 && e.key.repeat == 0) {
			onEvent(e);
			
		}
	}

}

bool GameController::quitGame() {
	
	gameIsOver->displayAreYouSure();
	if (gameIsOver->handleAreYouSure()) {
		running = !running;
		return true;
	}
	else {
		
		return false;
	}
	
}


void GameController::onEvent(SDL_Event &e) {
		//Actions keyboard events
	
		if (e.type == SDL_QUIT)
			//User requests quit
		{
			if (!quitGame()) {
				gameTiles->drawTiles();
			}
			
		}
		
		else if (e.type == SDL_KEYDOWN)
			//user presses a key
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_RETURN:
				updateRunning();

			case SDLK_UP:

				gameTiles->moveTile(Direction::UP);
				if (gameTiles->checkSolved()) {
					gameWon();
				}
				break;

			case SDLK_DOWN:
				gameTiles->moveTile(Direction::DOWN);
				if (gameTiles->checkSolved()) {
				gameWon();
				}
				break;

			case SDLK_LEFT:
				gameTiles->moveTile(Direction::LEFT);
				if (gameTiles->checkSolved()) {
					gameWon();
				}
				break;

			case SDLK_RIGHT:
				gameTiles->moveTile(Direction::RIGHT);
				if (gameTiles->checkSolved()) {
					gameWon();
				}
				break;
			}
			
		}
		

}
void GameController::updateStarted() {
	started = !started;
}

void GameController::gameWon() {
	SDL_Delay(500);
	gameIsOver->congratulations();
	if (gameIsOver->handlePlayAgain()) {
		choosePic();
	}
	else {
		updateRunning();
	}	
}

GameController::~GameController() {

}