#ifndef GAME_HPP
#define GAME_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_mixer.h>
#include <string>
#include <iostream>
#include <vector>
#include "Rect.h"
//using namespace std;

class game
{
private:
	bool is_running;
	bool isObstacleBulletCollision;
	SDL_Window *window;
	SDL_Texture *backgrnd;
	SDL_Texture *CurrScore_tex;
	SDL_Texture *Show_Ammo;
	SDL_Rect Ammo_rect;
	SDL_Rect Score_rect;
	SDL_Rect Display_rect;
	SDL_Rect Display_rect2;
	SDL_Rect Back_rect;
	SDL_Rect Back_rect2;
	Rect *rect;
	Rect *rect2;
	double Curr_Score;
	long long int x_back;

public:
	// SDL_Window *window;
	game();
	~game();
	static SDL_Renderer *renderer;
	static SDL_Event *event;
	// static vector<Mix_Chunk *> audioList;
	double get_score();
	void init(const char *title, int xpos, int ypos, int width, int height, bool full_ornot);
	void HandleEvents();
	void update();
	void render();
	void generateObstacles();
	void obstacleCollisionDetection();
	void bulletAndObstacleCollisionDetection();
	void clean();
	void Update_Score_TexandAmmo();
	void Update_Background();
	void spawnRects(SDL_Renderer *renderer);
	void moveRects(SDL_Renderer *renderer);
	void drawMathRects(SDL_Renderer *renderer);
	void outOfAmmo();
	void mathRectCollisionDetection(SDL_Renderer *renderer);
	bool Is_Running()
	{
		return (is_running);
	};
};
#endif
