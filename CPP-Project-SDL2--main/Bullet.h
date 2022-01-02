#include "game_object.h"

class Bullet : public game_object
{
private:
    int window_height, window_width, height, width;
    float velocity = 10;

public:
    Bullet(const char *texturesheet, SDL_Renderer *ren, int x, int y, int window_height, int window_width, int height, int width) : game_object(texturesheet, ren, x, y)
    {
        this->window_height = window_height;
        this->window_width = window_width;
        this->height = height;
        this->width = width;

        // initialising the bullet
        src_rec.h = height;
        src_rec.w = width;
        src_rec.x = 0;
        src_rec.y = 0;
        des_rec.h = height / 10;
        des_rec.w = width / 10;
        des_rec.x = x;
        des_rec.y = y;
    };

    int getx();
    SDL_Rect getBulletRect();

    int getwidth();

    void update();
};
