#ifndef DEFAULTS_H
#define DEFAULTS_H
#include <string>
#include <memory>
#include "SDL.h"


class Defaults
{
private:
	//std::string gamePicture{"Images/rose.jpg"};
	const char* gamePicture{ "Images/rose.jpg" };
	const int SCREEN_WIDTH{ 600 };
	const int SCREEN_HEIGHT{ 640 };
	const int banner_height{ 40 };
	const int tile_no_across{ 3 }; // this could be chosen at startup
	const int tile_no_down{ 3 }; // this could be chosen at startup


	std::string game_font{ "Font/Gilsanub.ttf" }; //"Font/Gilsanub.ttf"
	const int h1_size{ 70 }; //70
	const int h2_size{ 40 }; //40
	const int h3_size{ 20 }; //20

	const uint8_t main_colour_red{ 0xfc }; // 0xfc
	const uint8_t main_colour_blue{ 0x12 }; // 0x12 
	const uint8_t main_colour_green{ 0xe5 }; // 0xe5

	const uint8_t sec_colour_red{ 0xff }; //0xff
	const uint8_t sec_colour_blue{ 0xff }; // 0xff
	const uint8_t sec_colour_green{ 0xff }; //0xff

public:
	Defaults();
	int get_screen_width() const;
	int get_screen_height() const;
	//std::string get_game_picture() const;
	const char* get_game_picture() const;
	int get_no_across() const;
	int get_no_down() const;
	int get_banner_height() const;
};

#endif