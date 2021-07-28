#include "SDL.h"
#include <iostream>
#include "gameController.h"

int main(int argc, char* args[]) {
	GameController newGame;
	newGame.startGame();
	return 0;
}

//TO ADD

//Bug on exit with X on congrats window (if choose N it doesn't go back to congrats window)
//upload own pic
//countdown option
//Timer and top scores
//Enter name if top score
//default green and blue possibly wrong way round (intro background)
// https://docs.microsoft.com/en-us/windows/win32/shell/common-file-dialog
 