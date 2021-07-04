#include "SDL.h"
#include <iostream>
#include "gameController.h"

int main(int argc, char* args[]) {
	GameController newGame;
	newGame.runGame();
	SDL_Delay(2000);

	return 0;
}