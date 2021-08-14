#include "SDL.h"
#include <iostream>
#include "gameController.h"

int main(int argc, char* args[]) {
	GameController newGame;
	newGame.startGame();
	return 0;
}

//TO ADD

//Check for const throughout
//Standardise the naming convention

//Congrats - make background flash and realign text

//Bug - Can't close program if y/n text waiting - Need to fix on Play again and deal with others as a new window.

//Upload image option
//Timer and top scores
//Enter name if top score
//default green and blue possibly wrong way round (intro background)
// https://docs.microsoft.com/en-us/windows/win32/shell/common-file-dialog
 