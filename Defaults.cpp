#include "Defaults.h"

Defaults::Defaults() {}

int Defaults::get_screen_width() const {
	return SCREEN_WIDTH;
}

int Defaults::get_screen_height() const {
	return SCREEN_HEIGHT;
}

std::string Defaults::get_game_font() const {
	return game_font;
}

std::string Defaults::get_intro_font() const {
	return intro_font;
}

std::string Defaults::get_game_name() const {
	return game_name;
}
std::string Defaults::get_game_intro() const {
	return start_game_text;
}
uint8_t Defaults::get_main_colour_red() const {
	return main_colour_red;
}
uint8_t Defaults::get_main_colour_blue() const {
	return main_colour_blue;
}
uint8_t Defaults::get_main_colour_green() const {
	return main_colour_green;
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

uint8_t Defaults::get_intro_background_colour_red() const {
	return intro_background_colour_red;
}
uint8_t Defaults::get_intro_background_colour_blue() const {
	return intro_background_colour_blue;
}
uint8_t Defaults::get_intro_background_colour_green() const {
	return intro_background_colour_green;
}