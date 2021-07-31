#ifndef GAMEOVER_H
#define GAMEOVER_H
#include "SDL.h"
#include "Defaults.h"

//#include "IRenderableText.h"
#include "gameWindow.h"
class gameOver
	//class to deal with end of game - are you sure you want to quit,congratulations,high score once timer sorted
{
private:
	std::shared_ptr<Defaults> game_defaults;
	std::shared_ptr<GameWindow> game_window;

public:
	gameOver(std::shared_ptr<Defaults> defaults, std::shared_ptr<GameWindow> window);
	void display_are_you_sure() const;
	bool handle_are_you_sure() const;

	void congratulations() const;
	bool handle_play_again() const;
};

#endif