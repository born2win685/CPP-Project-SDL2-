#pragma once
#include <SDL2/SDL.h>
#include <random>
#include <algorithm>

class Math
{
public:
    int choose_optype(int num_choices);
    int gen_addscore(int ammo);
    int gen_subscore(int ammo, int flag);
    int gen_addandsubscore(int ammo, int flag);
    double gen_addandmulscore(int ammo, int flag);
    int gen_subanddivscore(int ammo, int flag);
    SDL_Rect get_rect();
};