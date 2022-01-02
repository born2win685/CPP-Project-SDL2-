#ifndef TM_H
#define TM_H
#include"game.h"
#include<SDL2/SDL_image.h>

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* texture);
};

#endif 

