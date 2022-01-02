#include "game_object.h"

class BackGround : public game_object
{
private:
    int window_height, window_width;

public:
    BackGround(const char *texturesheet, SDL_Renderer *ren, int x, int y, int window_height, int window_width) : game_object(texturesheet, ren, x, y)
    {
        this->window_height = window_height;
        this->window_width = window_width;

        src_rec.h = window_height;
        src_rec.w = window_width;
        src_rec.x = 0;
        src_rec.y = 0;
        des_rec.h = window_height;
        des_rec.w = window_width;
        des_rec.x = 0;
        des_rec.y = 0;
    }
};