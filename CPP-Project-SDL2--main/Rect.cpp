#include "Rect.h"
#include <iostream>

Rect::Rect(SDL_Window *window, SDL_Renderer *renderer, int w, int h, int x, int y, int r, int g, int b, int a, SDL_Texture *Message)
{
    this->window = window;
    this->renderer = renderer;
    this->w = w;
    this->h = h;
    this->x = x;
    this->y = y;
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
    this->Message = Message;
    this->isCollisionDetected = false;
}

void Rect::draw()
{

    rect.w = w;
    rect.h = h;
    rect.x = x;
    rect.y = y;

    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderCopy(renderer, Message, NULL, &rect);
    SDL_RenderPresent(renderer);
}

void Rect::move()
{
    this->x -= 2;
    // std::cout << this->x << std::endl;
}

double Rect::getx()
{
    return x;
}

SDL_Rect Rect::get_rect()
{
    return rect;
}
