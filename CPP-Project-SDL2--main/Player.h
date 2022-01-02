#include "game_object.h"

class Player : public game_object
{
private:
    int ammo, window_height, window_width, player_height, player_width, platform_height;
    float gravity = 0.2, acceleration = 0.2, initial_velocity = 0, final_velocity = 0;
    bool space_pressed = false, shoot = false;

public:
    Player(const char *texturesheet, SDL_Renderer *ren, int x, int y, int window_height, int window_width, int player_height, int player_width, int platform_height) : game_object(texturesheet, ren, x, y)
    {
        this->window_height = window_height;
        this->window_width = window_width;
        this->player_height = player_height;
        this->player_width = player_width;
        this->platform_height = platform_height;
        this->ammo = 10;

        // initialising the player
        src_rec.h = player_height;
        src_rec.w = player_width;
        src_rec.x = 0;
        src_rec.y = 0;
        des_rec.h = player_height;
        des_rec.w = player_width;
        des_rec.x = 0;
        des_rec.y = window_height - src_rec.h - platform_height;
    };

    int getx();
    int gety();
    int get_ammo();
    void set_ammo(int ammo);
    void set_space_pressed(bool is_pressed);
    SDL_Rect getPlayerRect();

    void update();
};
