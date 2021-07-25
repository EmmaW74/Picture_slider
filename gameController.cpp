#include "gameController.h"
#include <iostream>
GameController::GameController() {
	game_defaults = std::make_shared<Defaults>();
	game_window = std::make_shared<GameWindow>(game_defaults);
	//game_tiles = std::make_shared<TileManager>(game_defaults, game_window);
	game_intro = std::make_shared<Intro>(game_defaults,game_window);
	started = false;
	running = false;
}

void GameController::update_running() {
	running = !running;
}
void GameController::startGame() {
	
	game_intro->run_intro();
	SDL_Event e;
	while (!started) {
		if (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT)
				//User requests quit
			{
				update_started();
				quitGame();
			}
			else if (e.type == SDL_KEYDOWN) {

				if (e.key.keysym.sym == SDLK_RETURN) {
					update_started();
					choosePic();
					
				}
			}
		}
	}
}

void GameController::choosePic() {
	bool picked = false;
	game_intro->display_pics();
	game_intro->highlight_pic(game_defaults->get_current_pic());
	SDL_Event e;
	while (!picked) {
		if (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT)
				//User requests quit
			{
				picked = true;
				quitGame();
			}
			else if (e.type == SDL_KEYDOWN) {

				if (e.key.keysym.sym == SDLK_LEFT) {
					game_intro->update_selection(Direction::LEFT);

				} else if (e.key.keysym.sym == SDLK_RIGHT) {
					game_intro->update_selection(Direction::RIGHT);
				}
				else if (e.key.keysym.sym == SDLK_RETURN) {
					picked = true;
					runGame();
				}
			}
		}
	}
}

void GameController::runGame() {
	running = true;
	game_tiles = std::make_shared<TileManager>(game_defaults, game_window);

	//game_tiles->draw_tiles();

	game_tiles->create_tile_list();
	game_tiles->draw_tiles();
	SDL_Delay(2000);
	game_tiles->shuffle_tile_list();
	game_tiles->draw_tiles();
	//SDL_Delay(2000);
	SDL_Event e;
	while (running) {
		if (SDL_PollEvent(&e) != 0 && e.key.repeat == 0) {
			onEvent(e);
			
		}
	}

}

void GameController::quitGame() {
	//running = false;
	running = !running;
}


void GameController::onEvent(SDL_Event &e) {
		//Actions keyboard events
	
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
			case SDLK_RETURN:
				update_running();

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
void GameController::update_started() {
	started = !started;
}

void GameController::gameWon() {
	std::cout << "GAME WON!!!" << std::endl;
}

GameController::~GameController() {

}