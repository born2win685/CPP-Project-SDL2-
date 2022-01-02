
#include <random>
#include "Obstacle.h"
#include "TextureManager.h"
#include "game.h"
#include "game_object.h"

/*
 *
 * @ref https://stackoverflow.com/a/19728404/15069364
 */
int Obstacle::generateRandomNumber(int min, int max)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(min, max);
    auto random_integer = uni(rng);
    return random_integer;
    // static bool flag = true;
    // if (flag)
    // {
    //     srand(time(NULL));
    //     flag = false;
    // }
    // return min + rand() % ((max + 1) - min);
}

void Obstacle::update(double delta_time, double rate)
{
    xpos -= (rate * delta_time);
    rate += delta_time;
    des_rec.x = xpos;
}

void Obstacle::render()
{
    SDL_RenderCopy(game::renderer, object_Tex, NULL, &des_rec);
    // SDL_RenderCopyEx(game::renderer, object_Tex, NULL, &des_rec, angle, NULL, SDL_FLIP_NONE);
}

int Obstacle::getXPos()
{
    return des_rec.x;
}

int Obstacle::getYPos()
{
    return des_rec.y;
}

SDL_Rect Obstacle::getObstacleRect()
{
    return des_rec;
}
