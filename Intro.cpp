#include "Intro.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_render.h"
#include <sstream>
#include <iostream>


Intro::Intro(std::shared_ptr<Defaults> gameDefaults, std::shared_ptr<GameWindow> window) :
	gameDefaults{ gameDefaults }, gameWindow{ window } {
}

void Intro::runIntro() {
	//calls methods to display intro screen
	gameWindow->fillBackground();
	renderTitle();
	renderIntroText();
}

void Intro::renderTitle() {
	//Add title and intro text to renderer and publish to screen
	std::istringstream iss{ gameDefaults->getGameName() };
	std::string line1{};
	std::string line2{};
	iss >> line1 >> line2;

	int y = (gameDefaults->getScreenHeight() / 5);
	int size = 100;
	RenderableText titleLine1{ y,gameDefaults->getIntroFont(),line1,size,gameDefaults,gameDefaults->getMainColourRed(),gameDefaults->getMainColourGreen(),gameDefaults->getMainColourBlue() };
	titleLine1.renderObjectLeft(gameWindow,-5);
	
	y = (gameDefaults->getScreenHeight() / 5) + size;
	RenderableText titleLine2{ y,gameDefaults->getIntroFont(),line2,size,gameDefaults,gameDefaults->getMainColourRed(),gameDefaults->getMainColourGreen(),gameDefaults->getMainColourBlue() };
	titleLine2.renderObjectRight(gameWindow);

	
}

void Intro::renderChoosePicText() {
	int y = gameDefaults->getScreenHeight() / 10;
	int size = 26;
	RenderableText choosePic{ y,gameDefaults->getGameFont(),gameDefaults->getChoosePicText(),size,gameDefaults,gameDefaults->getMainColourRed(),gameDefaults->getMainColourGreen(),gameDefaults->getMainColourBlue() };
	choosePic.renderObject(gameWindow->getMyRenderer());
	gameWindow->publishTexture();
}

void Intro::renderIntroText() {
	int y = (gameDefaults->getScreenHeight() / 10)*7;
	int size = 30;
	RenderableText choosePic{ y,gameDefaults->getGameFont(),gameDefaults->getGameIntro(),size,gameDefaults,gameDefaults->getMainColourRed(),gameDefaults->getMainColourGreen(),gameDefaults->getMainColourBlue() };
	choosePic.renderObject(gameWindow->getMyRenderer());
	gameWindow->publishTexture();
}

SDL_Texture* Intro::uploadPic(const char* picFile) {
	//Uploads picture file and returns as a texture
	SDL_Surface* tempSurface = IMG_Load(picFile);
	if (tempSurface == NULL)
	{
		std::cout << "uploadPic: Unable to load image" << SDL_GetError() << std::endl;
	}
	else {

		SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(gameWindow->getMyRenderer(), tempSurface);
		if (tempTexture == NULL)
		{
			std::cout << "RenderableImage: Unable to create texture" << std::endl;
		}
		else
		{
			SDL_FreeSurface(tempSurface);
			return tempTexture;
		}
	}
}

	void Intro::displayPics() {
		//Displays 4 pics on screen ready to choose
		gameWindow->fillBackground();
		SDL_Rect temp{};
		temp.w = (gameDefaults->getScreenHeight() / 7) * 2;
		temp.h = (gameDefaults->getScreenHeight() / 7) * 2;
		
		SDL_Texture* tempTexture;
		int pic = 0;
		for (int y =1; y < 5; y += 3) {
			int startX = (gameDefaults->getScreenWidth() - (temp.w * 3)) / 2;
			for (int x = 0; x < 3; x+=2) {
				tempTexture = uploadPic(gameDefaults->getGamePicture(pic));
				temp.x = startX + (x * temp.w);
				temp.y = ((gameDefaults->getScreenHeight() / 7) * y)+gameDefaults->getBannerHeight();
				SDL_RenderCopy(gameWindow->getMyRenderer(), tempTexture, NULL, &temp);
				pic++;
			}
		}
		renderChoosePicText();
		
	}
	void Intro::highlightPic(int pos) {
		//Draws calls function to draw rect around selected picture
		gameWindow->fillBackground();
		displayPics();

		int picDimension = ((gameDefaults->getScreenHeight() / 7) * 2);
		int startX = ((gameDefaults->getScreenWidth() - (3 * picDimension))) / 2;
		int startY = ((gameDefaults->getScreenHeight() / 7)) + gameDefaults->getBannerHeight(); //6
		SDL_Rect outlineRect{};
		outlineRect.w = picDimension;
		outlineRect.h = picDimension;
		//outlineRect.x = (picDimension + ((pos % 2) * (2 * picDimension)));
		outlineRect.x = ((startX + ((pos % 2) * (2 * picDimension))));
		//outlineRect.y = (picDimension + ((pos / 2) * (2 * picDimension)))+gameDefaults->getLeftMargin();
		outlineRect.y = startY + ((pos/2)*((gameDefaults->getScreenHeight() / 7) *3));
		gameWindow->drawRectangle(outlineRect, 6, gameDefaults);
		gameWindow->publishTexture();
	}

	void Intro::updateSelection(Direction direction){
		//Update default current picture and move highlight on screen based on direction argument
		
		if (direction == Direction::LEFT){
			if (gameDefaults->getCurrentPic() == 0) {
				gameDefaults->updateCurrentPic(3);
				highlightPic(3);
			}
			else {
				int temp = gameDefaults->getCurrentPic();
				temp--;
				gameDefaults->updateCurrentPic(temp);
				highlightPic(temp);
			}
		}
		else if (direction == Direction::RIGHT) {
		
			if (gameDefaults->getCurrentPic() == 3) {
				gameDefaults->updateCurrentPic(0);
				highlightPic(0);
			}
			else {
				int temp = gameDefaults->getCurrentPic();
				temp++;
				gameDefaults->updateCurrentPic(temp);
				highlightPic(temp);
			}
		}
	}





