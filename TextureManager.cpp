#include <SDL2/SDL_image.h>
#include"TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture, SDL_Renderer* ren)
{
	SDL_Surface* temp_surface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, temp_surface);
	SDL_FreeSurface(temp_surface);
	return(tex);
}