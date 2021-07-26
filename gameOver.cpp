#include "gameOver.h"
#include "SDL_ttf.h"
#include "SDL_render.h"
#include "SDL.h"

gameOver::gameOver(std::shared_ptr<Defaults> defaults, std::shared_ptr<GameWindow> window):
	game_defaults{ defaults }, game_window{ window } {

}
void gameOver::display_are_you_sure() const {
	game_window->fill_background();
	//Add text to renderer and publish to screen

	//open font and set font colour
	TTF_Init();
	TTF_Font* font = TTF_OpenFont(game_defaults->get_game_font().c_str(), 26);
	SDL_Color color = { game_defaults->get_main_colour_red(), game_defaults->get_main_colour_green(), game_defaults->get_main_colour_blue() };

	//Add text to screen

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, game_defaults->get_are_you_sure_text().c_str(), color);
	SDL_Texture* textureMessage = SDL_CreateTextureFromSurface(game_window->get_myRenderer(), surfaceMessage);
	SDL_Rect rect{ };
	rect.w = surfaceMessage->w;
	rect.h = surfaceMessage->h;
	rect.x = (game_defaults->get_screen_width() - rect.w) / 2;
	rect.y = game_defaults->get_screen_height() / 2;
	SDL_RenderCopy(game_window->get_myRenderer(), textureMessage, NULL, &rect);
	game_window->publishTexture();

	//free surface and quit TTF
	SDL_FreeSurface(surfaceMessage);
	TTF_Quit();
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

}