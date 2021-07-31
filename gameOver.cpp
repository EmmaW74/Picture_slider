#include "gameOver.h"
#include "SDL_ttf.h"
#include "SDL_render.h"
#include "SDL.h"
#include "RenderableText.h"

gameOver::gameOver(std::shared_ptr<Defaults> defaults, std::shared_ptr<GameWindow> window):
	game_defaults{ defaults }, game_window{ window } {

}
void gameOver::display_are_you_sure() const {
	game_window->fill_background();
	int y = game_defaults->get_screen_height() / 2;
	int size = 26;
	RenderableText are_you_sure{ y,game_defaults->get_game_font(),game_defaults->get_are_you_sure_text(),size,game_defaults };
	are_you_sure.render_object(game_window->get_myRenderer());
	game_window->publishTexture();
}

bool gameOver::handle_are_you_sure() const {
	bool waiting = true;
	SDL_Event e;
	while (waiting) {
		if (SDL_PollEvent (&e) !=0) {
			if (e.type == SDL_KEYDOWN) {

			if (e.key.keysym.sym == SDLK_y) {
				waiting = !waiting;
				return true;
			}
			else if (e.key.keysym.sym == SDLK_n) {
				waiting = !waiting;
				return false;
			}
		}
		}
	}

}

void gameOver::congratulations() const {
	//Add congrats and play again text to renderer and publish to screen
	game_window->fill_background();

	int y = game_defaults->get_screen_height() / 3;
	int size = 40;
	RenderableText congrats{ y,game_defaults->get_intro_font(),game_defaults->get_congrats_text(),size,game_defaults };
	congrats.render_object(game_window->get_myRenderer());
	SDL_Delay(1000);

	y = game_defaults->get_screen_height() / 2;
	size = 26;
	RenderableText play_again{ y,game_defaults->get_game_font(),game_defaults->get_play_again_text(),size,game_defaults };
	play_again.render_object(game_window->get_myRenderer());
	game_window->publishTexture();
}

bool gameOver::handle_play_again() const {
	//THIS CAN POSSIBLY BE MERGED WITH OTHER HANDLE Y/N METHODS
	bool waiting = true;
	SDL_Event e;
	while (waiting) {
		if (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_KEYDOWN) {

				if (e.key.keysym.sym == SDLK_y) {
					waiting = !waiting;
					return true;
				}
				else if (e.key.keysym.sym == SDLK_n) {
					waiting = !waiting;
					return false;
				}
			}
		}
	}

}