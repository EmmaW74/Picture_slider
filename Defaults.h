#ifndef DEFAULTS_H
#define DEFAULTS_H
#include <string>
#include <memory>
#include <vector>
#include "SDL.h"


class Defaults
{
private:
	//std::string gamePicture{"Images/rose.jpg"};
	std::vector<const char*> gamePicture{ "Images/rose.jpg","Images/butterfly.jpg","Images/mixture.jpg","Images/chain.jpg" };
	int current_pic = 0;
	const int SCREEN_WIDTH{ 600 };
	const int SCREEN_HEIGHT{ 640 };
	const int banner_height{ 40 };
	const int tile_no_across{ 4 }; // this could be chosen at startup
	const int tile_no_down{ 4 }; // this could be chosen at startup


	std::string game_font{ "Font/Gilsanub.ttf" }; //"Font/Gilsanub.ttf"
	std::string intro_font{ "Font/SEGALOGOFONT400.ttf" };
	const int h1_size{ 70 }; //70
	const int h2_size{ 40 }; //40
	const int h3_size{ 20 }; //20

	//Intro background colour 331832
	
	const uint8_t intro_background_colour_red{ 0x33 };  
	const uint8_t intro_background_colour_blue{ 0x18 };  
	const uint8_t intro_background_colour_green{ 0x32 };  

	//main text colour 9FC2CC
	const uint8_t main_colour_red{ 0x9F };  
	const uint8_t main_colour_blue{ 0xC2 };  
	const uint8_t main_colour_green{ 0xCC };  

	//secondary colour - not in use yet 694D75
	const uint8_t sec_colour_red{ 0x69 };  
	const uint8_t sec_colour_blue{ 0x4D };  
	const uint8_t sec_colour_green{ 0x75 };  

	//Text for intro pages

	const std::string game_name{ "SLIDE PIX" };
	const std::string start_game_text{ "To start press ENTER" };
	const std::string choose_pic_text{ "Choose a picture then press ENTER" };


public:
	Defaults();
	int get_screen_width() const;
	int get_screen_height() const;
	//std::string get_game_picture() const;
	int get_current_pic() const;
	void update_current_pic(int new_choice);
	const char* get_gamePicture(int x) const;
	int get_no_across() const;
	int get_no_down() const;
	int get_banner_height() const;
	std::string get_game_font() const;
	std::string get_intro_font() const;
	std::string get_game_name() const;
	std::string get_game_intro() const;
	

	uint8_t get_main_colour_red() const;
	uint8_t get_main_colour_blue() const;
	uint8_t get_main_colour_green() const;

	uint8_t get_intro_background_colour_red() const;
	uint8_t get_intro_background_colour_blue() const;
	uint8_t get_intro_background_colour_green() const;

};

#endif