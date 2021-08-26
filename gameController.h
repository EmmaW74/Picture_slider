#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include "gameWindow.h"
#include "TileManager.h"
#include "Intro.h"
#include "gameOver.h"
#include "Defaults.h"
#include <memory>

class GameController
	//controls the flow of the game
{
private:
	std::shared_ptr<Intro> gameIntro;
	std::shared_ptr<GameWindow> gameWindow;
	std::shared_ptr<Defaults> gameDefaults;
	std::shared_ptr<TileManager> gameTiles;
	std::shared_ptr<gameOver> gameIsOver;
	bool running;
	bool started;

public:
	GameController();
	void startGame();
	void choosePic();
	void runGame();
	void updateRunning();
	void updateStarted();
	void gameWon();
	bool quitGame();
	void resetGame();
	void onEvent(SDL_Event &e);
	~GameController();

};

#endif

