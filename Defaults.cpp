#include "Defaults.h"

Defaults::Defaults() {}

int Defaults::get_screen_width() const {
	return SCREEN_WIDTH;
}

int Defaults::get_screen_height() const {
	return SCREEN_HEIGHT;
}

//std::string Defaults::get_game_picture() const {
const char* Defaults::get_game_picture() const {
	return gamePicture;
}

int Defaults::get_no_across() const {
	return tile_no_across;
}

int Defaults::get_no_down() const {
	return tile_no_down;
}

int Defaults::get_banner_height() const {
	return banner_height;
}