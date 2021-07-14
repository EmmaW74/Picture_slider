#include "IRenderableText.h"
#include "SDL_ttf.h"

RenderableText::RenderableText(int x, int y, std::string font, std::string text, uint8_t red, uint8_t blue, uint8_t green):
x{x}, y{y},text{text}, colour_red{red},colour_green{green},colour_blue{blue}{}

int RenderableText::get_x() const {
	return x;
}

int RenderableText::get_y() const {
	return y;
}


std::string RenderableText::get_text() const {
	return text;
}

void RenderableText::update_text(std::string newtext) {
	text = newtext;
}

uint8_t RenderableText::get_colour_red() const {
	return colour_red;
}

uint8_t RenderableText::get_colour_blue() const {
	return colour_blue;
}

uint8_t RenderableText::get_colour_green() const {
	return colour_green;
}

void RenderableText::draw_element(SDL_Renderer* myRenderer) {
	//creates a texture for the text and copies to myRenderer ready to publish
	TTF_Init();
	TTF_Font* font = TTF_OpenFont(game_defaults->get_game_font().c_str(), 200); //this opens a font style and sets a size
	SDL_Color color = { colour_red, colour_green, colour_blue };
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), color); //Create surface first
	SDL_Texture* textureMessage = SDL_CreateTextureFromSurface(myRenderer, surfaceMessage); //Convert to texture


	SDL_Rect Message_rect;
	Message_rect.x = get_x();
	Message_rect.y = get_y();
	Message_rect.w = surfaceMessage->w;
	Message_rect.h = surfaceMessage->h;

	SDL_RenderCopy(myRenderer, textureMessage, NULL, &Message_rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(textureMessage);
}