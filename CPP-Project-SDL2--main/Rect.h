#pragma once
#include <SDL2/SDL.h>
class Rect
{
public:
    Rect(SDL_Window *window, SDL_Renderer *renderer, int w, int h, int x, int y, int r, int g, int b, int a, SDL_Texture *Message);
    void draw();
    void move();
    double getx();
    SDL_Rect get_rect();
    bool isCollisionDetected;

private:
    int w, h, x, y, r, g, b, a;

    SDL_Rect rect;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *Message;
};