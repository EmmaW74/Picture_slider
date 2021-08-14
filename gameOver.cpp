#include "gameOver.h"
#include "SDL_ttf.h"
#include "SDL_render.h"
#include "SDL.h"
#include "RenderableText.h"

gameOver::gameOver(std::shared_ptr<Defaults> defaults, std::shared_ptr<GameWindow> window):
	gameDefaults{ defaults }, gameWindow{ window } {

}
void gameOver::displayAreYouSure() const {
	gameWindow->fillBackground();
	int y = gameDefaults->getScreenHeight() / 2;
	int size = 26;
	RenderableText areYouSure{ y,gameDefaults->getGameFont(),gameDefaults->getAreYouSureText(),size,gameDefaults,gameDefaults->getMainColourRed(),gameDefaults->getMainColourGreen(),gameDefaults->getMainColourBlue() };
	areYouSure.renderObject(gameWindow->getMyRenderer());
	gameWindow->publishTexture();
}

bool gameOver::handleAreYouSure() const {
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

	int y = gameDefaults->getScreenHeight() / 3;
	int size = 60;
	RenderableText congrats{ y,gameDefaults->getGameFont(),gameDefaults->getCongratsText(),size,gameDefaults,gameDefaults->getsecondaryColourRed(),gameDefaults->getsecondaryColourGreen(),gameDefaults->getsecondaryColourBlue(), };
	congrats.changeX(gameDefaults->getGridWidth());
	congrats.renderObject(gameWindow->getMyRenderer());
	SDL_Delay(1000);

	y = gameDefaults->getScreenHeight() / 2;
	size = 26;
	RenderableText playAgain{ y,gameDefaults->getGameFont(),gameDefaults->getPlayAgainText(),size,gameDefaults ,gameDefaults->getsecondaryColourRed(),gameDefaults->getsecondaryColourGreen(),gameDefaults->getsecondaryColourBlue() };
	playAgain.changeX(gameDefaults->getGridWidth());
	playAgain.renderObject(gameWindow->getMyRenderer());
	gameWindow->publishTexture();
}

bool gameOver::handlePlayAgain() const {
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