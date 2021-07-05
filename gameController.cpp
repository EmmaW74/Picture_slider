#include "gameController.h"
#include <iostream>
GameController::GameController() {
	game_defaults = std::make_shared<Defaults>();
	game_window = std::make_shared<GameWindow>(game_defaults);
	game_tiles = std::make_shared<TileManager>(game_defaults, game_window);
	running = false;
}

void GameController::startGame() {
	
}

void GameController::runGame() {
	running = true;
	//game_tiles->draw_tiles();
	game_tiles->create_tile_list();
	game_tiles->draw_tiles();
	SDL_Delay(2000);
	game_tiles->shuffle_tile_list();
	game_tiles->draw_tiles();
	SDL_Delay(2000);
	SDL_Event e;
	while (running) {
		if (SDL_PollEvent(&e) != 0 && e.key.repeat == 0) {
			onEvent(e);
			
		}
	}

}

void GameController::quitGame() {
	running = false;
}


void GameController::onEvent(SDL_Event &e) {
		//Actins keyboard events
		if (e.type == SDL_QUIT)
			//User requests quit
		{
			quitGame();
		}
		else if (e.type == SDL_KEYDOWN)
			//user presses a key
		{
			switch (e.key.keysym.sym)
			{


			case SDLK_UP:

				game_tiles->move_tile(Direction::UP);
				if (game_tiles->check_solved()) {
					gameWon();
				}
				break;

			case SDLK_DOWN:
				game_tiles->move_tile(Direction::DOWN);
				if (game_tiles->check_solved()) {
					gameWon();
				}
				break;

			case SDLK_LEFT:
				game_tiles->move_tile(Direction::LEFT);
				if (game_tiles->check_solved()) {
					gameWon();
				}
				break;

			case SDLK_RIGHT:
				game_tiles->move_tile(Direction::RIGHT);
				if (game_tiles->check_solved()) {
					gameWon();
				}
				break;
			}
			
		}
		

}

void GameController::gameWon() {
	std::cout << "GAME WON!!!" << std::endl;
}

GameController::~GameController() {

}