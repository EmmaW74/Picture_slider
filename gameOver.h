#ifndef gameOver_H
#define gameOver_H
#include "SDL.h"
#include "Defaults.h"
#include "gameWindow.h"

class gameOver
	//class to deal with end of game - are you sure you want to quit,congratulations (Future - high score once timer sorted)
{
private:
	std::shared_ptr<Defaults> gameDefaults;
	std::shared_ptr<GameWindow> gameWindow;

public:
	gameOver(std::shared_ptr<Defaults> defaults, std::shared_ptr<GameWindow> window);
	void displayAreYouSure() const;
	bool handleAreYouSure() const;
	void congratulations() const;
	bool handlePlayAgain() const;
};

#endif