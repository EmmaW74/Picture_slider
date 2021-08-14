#ifndef RENDER_H
#define RENDER_H
#include "Defaults.h"

class Render
{
private:

	int y;
	std::shared_ptr<Defaults> game_defaults;
	SDL_Surface* objectSurface;
	SDL_Texture* objectTexture;

public:
	virtual void render_object() = 0;

};
#endif

