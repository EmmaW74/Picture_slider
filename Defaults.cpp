#include "Defaults.h"

Defaults::Defaults() {}

const int Defaults::getScreenWidth() const {
	return screenWidth;
}

const int Defaults::getScreenHeight() const {
	return screenHeight;
}

const int Defaults::getGridWidth() const {
	return gridWidth;
}
const int Defaults::getGridHeight() const {
	return gridHeight;
}

const std::string Defaults::getGameFont() const {
	return gameFont;
}

const std::string Defaults::getIntroFont() const {
	return introFont;
}

const std::string Defaults::getGameName() const {
	return gameName;
}
const std::string Defaults::getGameIntro() const {
	return startGameText;
}
const uint8_t Defaults::getMainColourRed() const {
	return mainColourRed;
}
const uint8_t Defaults::getMainColourBlue() const {
	return mainColourBlue;
}
const uint8_t Defaults::getMainColourGreen() const {
	return mainColourGreen;
}

const int Defaults::getNoAcross() const {
	return tileNoAcross;
}

const int Defaults::getNoDown() const {
	return tileNoDown;
}

const char* Defaults::getGamePicture(const int x) const {
	if (x < gamePicture.size()) {
		return gamePicture.at(x);
	}
	else return gamePicture.at(0);
}

const int Defaults::getBannerHeight() const {
	return bannerHeight;
}

const uint8_t Defaults::getIntroBackgroundColourRed() const {
	return introBackgroundColourRed;
}
const uint8_t Defaults::getIntroBackgroundColourBlue() const {
	return introBackgroundColourBlue;
}
const uint8_t Defaults::getIntroBackgroundColourGreen() const {
	return introBackgroundColourGreen;
}

void Defaults::updateCurrentPic(int newChoice) {
	currentPic = newChoice;
}

int Defaults::getCurrentPic() const {
	return currentPic;
}

const std::string Defaults::getChoosePicText() const {
	return choosePicText;
}

const std::string Defaults::getAreYouSureText() const {
	return areYouSureText;
}

const std::string Defaults::getCongratsText() const {
	return congratsText;
}

const std::string Defaults::getPlayAgainText() const {
	return playAgainText;
}

const int Defaults::getLeftMargin() const {
	return leftMargin;
}

const uint8_t Defaults::getsecondaryColourRed() const{
	return secondaryColourRed;
}
const uint8_t Defaults::getsecondaryColourBlue() const{
	return secondaryColourBlue;
}
const uint8_t Defaults::getsecondaryColourGreen() const{
	return secondaryColourGreen;
}