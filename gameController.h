#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include "gameWindow.h"
#include "TileManager.h"
#include <memory>

class GameController
{
private:
	std::shared_ptr<GameWindow> game_window;
	std::shared_ptr<Defaults> game_defaults;
	std::shared_ptr<TileManager> game_tiles;
	bool running;

public:
	GameController();
	void startGame();
	void runGame();
	//void endGame();
	void gameWon();
	void quitGame();
	void onEvent(SDL_Event &e);
	~GameController();

};

#endif

