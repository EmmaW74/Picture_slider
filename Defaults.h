#ifndef DEFAULTS_H
#define DEFAULTS_H
#include <string>
#include <memory>
#include <vector>
#include "SDL.h"


class Defaults
	//stores default game and format settings 
{
private:
	//image, screen and grid defaults
	const std::vector<const char*> gamePicture{ "Images/rose.jpg","Images/poppy.jpg","Images/mixture.jpg","Images/chain.jpg" };
	int currentPic = 0;
	const int screenWidth{ 1000 };
	const int screenHeight{ 640 };
	const int gridWidth{ 600 };
	const int gridHeight{ 600 };
	const int bannerHeight{ 20 };
	const int leftMargin{ 20 };
	const int tileNoAcross{ 2 }; // Future - this could be chosen at startup
	const int tileNoDown{ 2 }; // Future - this could be chosen at startup

	//font settings
	const std::string gameFont{ "Font/Ravie.ttf" };
	const std::string introFont{ "Font/SEGALOGOFONT400.ttf" }; 
	const int h1Size{ 70 };
	const int h2Size{ 40 };
	const int h3Size{ 20 };

	
	//colour settings 
	const uint8_t introBackgroundColourRed{ 0x3D };
	const uint8_t introBackgroundColourBlue{ 0x3B };
	const uint8_t introBackgroundColourGreen{ 0x30 };

	const uint8_t mainColourRed{ 0xE9 };
	const uint8_t mainColourBlue{ 0xED };
	const uint8_t mainColourGreen{ 0xDE };
	
	const uint8_t secondaryColourRed{ 0xFF };  //E7
	const uint8_t secondaryColourBlue{ 0x00 }; //47 
	const uint8_t secondaryColourGreen{ 0x00 }; //E2
	 
	//default text
	const std::string gameName{ " SLIDE PIX" };
	const std::string startGameText{ "To start press ENTER" };
	const std::string choosePicText{ "Choose a picture" };
	const std::string areYouSureText{ "Are you sure you want to quit? Y/N" };
	const std::string congratsText{ "WELL DONE!!" }; 
	const std::string playAgainText{ "Play again? Y/N" };


public:
	Defaults();
	void updateCurrentPic(const int newChoice);

	//gets
	const int getScreenWidth() const;
	const int getScreenHeight() const;
	const int getGridWidth() const;
	const int getGridHeight() const;
	const int getNoAcross() const;
	const int getNoDown() const;
	const int getBannerHeight() const;
	const int getLeftMargin() const;

	int getCurrentPic() const;
	const char* getGamePicture(int x) const;

	const std::string getGameFont() const;
	const std::string getIntroFont() const;

	const std::string getGameName() const;
	const std::string getGameIntro() const;
	const std::string getChoosePicText() const;
	const std::string getAreYouSureText() const;
	const std::string getCongratsText() const;
	const std::string getPlayAgainText() const;

	const uint8_t getMainColourRed() const;
	const uint8_t getMainColourBlue() const;
	const uint8_t getMainColourGreen() const;
	const uint8_t getsecondaryColourRed() const;
	const uint8_t getsecondaryColourBlue() const;
	const uint8_t getsecondaryColourGreen() const;

	const uint8_t getIntroBackgroundColourRed() const;
	const uint8_t getIntroBackgroundColourBlue() const;
	const uint8_t getIntroBackgroundColourGreen() const;

};

#endif