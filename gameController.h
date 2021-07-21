#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include "gameWindow.h"
#include "TileManager.h"
#include "Intro.h"
#include <memory>

class GameController
{
private:
	std::shared_ptr<Intro> game_intro;
	std::shared_ptr<GameWindow> game_window;
	std::shared_ptr<Defaults> game_defaults;
	std::shared_ptr<TileManager> game_tiles;
	bool running;
	//int current_pic_selection;

public:
	GameController();
	void startGame();
	void choosePic();
	void runGame();
	void update_running();
	//void endGame();
	void gameWon();
	void quitGame();
	void onEvent(SDL_Event &e);
	~GameController();

};

#endif

