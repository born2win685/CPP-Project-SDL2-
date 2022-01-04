#include <vector>
#include <string>
#include "game.h"
#include "Player.h"
#include "TextureManager.h"
#include "game_object.h"
#include "Bullet.h"
#include "Obstacle.h"
#include "Rect.h"
#include "Math.h"
#include "Homescreen.h"

SDL_Renderer *game ::renderer = NULL;
vector<Bullet *> bullets;
Player *player;
vector<Obstacle *> obsList;
//vector<Mix_Chunk *> game::audioList;
// int ammo = 10;
int ammo1 = 0;
int ammo2 = 0;
int flag=1;
double ammo_mul = 1;
int op1 = 0;
int op2 = 0;

#define window_height 600
#define window_width 1500

game::game()
{
}

game ::~game()
{
}

void game::init(const char *title, int xpos, int ypos, int width, int height, bool full_ornot)
{
	//int flag = 0;
	if (full_ornot)
	{
		flag = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flag);

		if (window)
		{
			cout << "Window Created" << endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			cout << "Renderer Created" << endl;
		}
		is_running = true;
	}
	else
	{
		is_running = false;
	}
	TTF_Init();

	// Create Game_objects
	CurrScore_tex = NULL;
	Curr_Score = 0;
	x_back = 0;

	backgrnd = TextureManager::LoadTexture("assets/background.png");
	player = new Player("assets/player.png", renderer, 0, 0, window_height, window_width, 85, 77, 65);

	Display_rect.x = 0;
	Display_rect.y = 0;
	Display_rect.w = window_width;
	Display_rect.h = window_height;

	Back_rect.x = x_back;
	Back_rect.y = 0;
	Back_rect.h = window_height;
	Back_rect.w = window_width;

	Back_rect2.x = 0;
	Back_rect2.y = 0;
	Back_rect2.h = window_height;
	Back_rect2.w = window_width;

	Score_rect.x = 1200;
	Score_rect.y = 0;
	Score_rect.w = 300;
	Score_rect.h = 80;

	Ammo_rect.x = 0;
	Ammo_rect.y = 530;
	Ammo_rect.w = 250;
	Ammo_rect.h = 70;

	Update_Background();
	Update_Score_TexandAmmo();
}

void game::HandleEvents() // Handle Various events happening
{
	SDL_Event event;
	SDL_PollEvent(&event);
	const Uint8 *keystates = SDL_GetKeyboardState(NULL);

	if (event.type == SDL_QUIT)
	{
		is_running = false;
	}

	if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_RETURN)
		{
			if (player->get_ammo() > 0)
			{
				bullets.push_back(new Bullet("assets/bullet.png", renderer, player->getx(), player->gety(), window_height, window_width, 595, 420));
				player->set_ammo(player->get_ammo() - 1);
			}
		}
	}

	if (keystates[SDL_SCANCODE_SPACE])
	{
		// Event for jump.
		player->set_space_pressed(true);
	}
	else
	{
		player->set_space_pressed(false);
	}
}

// Obstacles are handled here
void game::generateObstacles()
{
	Obstacle *obs = new Obstacle("assets/monster.png", game::renderer, window_width, window_height, 128, 128);
	obsList.push_back(obs);
	std::cout << "Obstacle Generated" << std::endl;
}

/*
 *@ref https://github.com/libsdl-org/SDL/blob/c59d4dcd38c382a1e9b69b053756f1139a861574/src/video/SDL_rect.c#L27
 */
void game::obstacleCollisionDetection()
{
	//Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048);
	//Mix_Chunk *endGame = Mix_LoadWAV("assets/music/gameExplosion.wav");
	//game::audioList.push_back(endGame);
	for (Obstacle *obs : obsList)
	{
		SDL_Rect obstacleRect = obs->getObstacleRect();
		SDL_Rect playerRect = player->getPlayerRect();
		SDL_bool hasIntersection = SDL_HasIntersection(&obstacleRect, &playerRect);
		if (hasIntersection == SDL_TRUE)
		{
			//Mix_PlayChannel(-1, endGame, 0);
			SDL_Delay(500);
			std::cout << "Collision Detected." << std::endl;
			//clean(game::audioList);
			is_running = false;
		}
	}
}

void game::bulletAndObstacleCollisionDetection()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		for (int j = 0; j < obsList.size(); j++)
		{
			SDL_Rect bulletRect = bullets[i]->getBulletRect();
			SDL_Rect obstacleRect = obsList[j]->getObstacleRect();
			SDL_bool hasIntersection = SDL_HasIntersection(&obstacleRect, &bulletRect);
			if (hasIntersection == SDL_TRUE)
			{
				bullets.erase(bullets.begin() + i);
				obsList.erase(obsList.begin() + j);
			}
		}
	}
}
void game::update() // Game Logic is Handled Here
{
	// Update your game objects here

	Back_rect.x = x_back;
	x_back += 10;

	player->update();
	for (int i = 0; i < obsList.size(); i++)
	{
		obsList[i]->update(1.0 / 3.0, 7);
		if (obsList[i]->getXPos() < 0)
		{
			obsList.erase(obsList.begin() + i);
			player->set_ammo(player->get_ammo() - 1);
		}
	}
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->update();
		if (bullets[i]->getx() > window_width + bullets[i]->getwidth())
		{
			bullets.erase(bullets.begin() + i);
		}
	}

	Curr_Score = Curr_Score + (0.167);
	Update_Background();
	Update_Score_TexandAmmo();
}

double game::get_score()
{
	return Curr_Score;
}
void game::render()
{
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, backgrnd, &Back_rect, &Display_rect);
	if (Back_rect.x > (4109 - 1500) && Back_rect.x < 4109)
	{
		SDL_RenderCopy(renderer, backgrnd, &Back_rect2, &Display_rect2);
		// cout << Back_rect.x << endl;
	}

	SDL_RenderCopy(renderer, CurrScore_tex, NULL, &Score_rect);
	SDL_RenderCopy(renderer, Show_Ammo, NULL, &Ammo_rect);
	player->Render();
	for (Bullet *bullet : bullets)
		bullet->Render();
	for (Obstacle *obs : obsList)
		obs->render();
	// SDL_RenderPresent(renderer);
}

void game::Update_Background()
{
	if (Back_rect.x + 1500 > 4109 && Back_rect.x < 4109)
	{
		Display_rect.w = 4109 - Back_rect.x;
		Display_rect2.x = Display_rect.w;
		Display_rect2.y = 0;
		Display_rect2.h = window_height;
		Display_rect2.w = window_width - Display_rect.w;

		Back_rect.w = Display_rect.w;
		Back_rect2.x = 0;
		Back_rect2.y = 0;
		Back_rect2.h = window_height;
		Back_rect2.w = window_width - Display_rect.w;
	}
	if (Back_rect.x < (4109 - 1500) && Back_rect.x >= 0)
	{
		Display_rect.w = window_width;
		Back_rect.w = window_width;
	}
	if (Back_rect.x > 4109)
	{
		Back_rect.x -= 4109;
		x_back = 0;
		Display_rect.w = window_width;
		Back_rect.w = window_width;
	}
}

void game::Update_Score_TexandAmmo()
{
	TTF_Font *Font = TTF_OpenFont("assets/Font.ttf", 24);
	if (Font == NULL)
	{
		cout << "Font is NULL" << endl;
	}
	SDL_Color White = {255, 255, 0};
	string s;
	s = to_string((long int)Curr_Score);
	s = "Score : " + s;
	SDL_Surface *surface = TTF_RenderText_Solid(Font, s.c_str(), White);
	CurrScore_tex = SDL_CreateTextureFromSurface(renderer, surface);

	s = to_string((long int)player->get_ammo());
	s = "Ammo : " + s;
	surface = TTF_RenderText_Solid(Font, s.c_str(), White);
	Show_Ammo = SDL_CreateTextureFromSurface(renderer, surface);

	if (CurrScore_tex == NULL)
	{
		cout << "Score Texture is NULL" << endl;
	}
	if (Show_Ammo == NULL)
	{
		cout << "Ammo Texture is NULL" << endl;
	}

	SDL_FreeSurface(surface);
	TTF_CloseFont(Font);
}
//int flag = 0;

void game::spawnRects(SDL_Renderer *renderer)
{
	TTF_Font *Sans = TTF_OpenFont("assets/Sans.ttf", 24);

	Math *math = new Math();

	/*int op1, op2;
	int operand1, operand2;
	double doperand2;*/
	string s1, s2;

	int optype = math->choose_optype(5);

	if (optype == 0)
	{
		int score_add1 = math->gen_addscore(player->get_ammo());
		int score_add2 = math->gen_addscore(player->get_ammo());
		s1 = "+" + to_string(score_add1);
		s2 = "+" + to_string(score_add2);
		ammo1 = score_add1;
		op1 = 0;
		ammo2 = score_add2;
		op2 = 0;
	}

	if (optype == 1)
	{
		int score_sub1 = math->gen_subscore(player->get_ammo(), 0);
		int score_sub2 = math->gen_subscore(player->get_ammo(), 1);

		s1 = "-" + to_string(score_sub1);
		s2 = "-" + to_string(score_sub2);

		ammo1 = score_sub1;
		op1 = 1;
		ammo2 = score_sub2;
		op2 = 1;
	}

	if (optype == 2)
	{
		int score_addandsub1 = math->gen_addandsubscore(player->get_ammo(), 0);
		int score_addandsub2 = math->gen_addandsubscore(player->get_ammo(), 1);

		s1 = "+" + to_string(score_addandsub1);
		s2 = "-" + to_string(score_addandsub2);

		ammo1 = score_addandsub1;
		op1 = 0;
		ammo2 = score_addandsub2;
		op2 = 1;
	}

	if (optype == 3)
	{
		int score_addandmul1 = (int)math->gen_addandmulscore(player->get_ammo(), 0);
		double score_addandmul2 = math->gen_addandmulscore(player->get_ammo(), 1);
		cout << score_addandmul2 << endl;

		double temp = (int)((score_addandmul2 * 100) + 0.5);
		score_addandmul2 = temp / 100;
		cout << score_addandmul2 << endl;
		s1 = "+" + to_string(score_addandmul1);
		s2 = "*" + to_string(score_addandmul2);
		s2 = s2.substr(0, 5);

		ammo1 = score_addandmul1;
		op1 = 0;

		ammo_mul = score_addandmul2;
		op2 = 2;
		/*temp = (double)player->get_ammo();
		temp *= score_addandmul2;
		ammo2 = (int)temp;*/
	}

	if (optype == 4)
	{
		int score_subanddiv1 = math->gen_subanddivscore(player->get_ammo(), 0);
		int score_subanddiv2 = math->gen_subanddivscore(player->get_ammo(), 1);

		s1 = "-" + to_string(score_subanddiv1);
		s2 = "/" + to_string(score_subanddiv2);

		ammo1 = score_subanddiv1;
		op1 = 1;
		ammo2 = score_subanddiv2;
		op2 = 3;
	}

	SDL_Color White = {255, 255, 255};

	SDL_Surface *surfaceMessage =
		TTF_RenderText_Solid(Sans, s1.c_str(), White);

	SDL_Texture *Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Surface *surfaceMessage2 =
		TTF_RenderText_Solid(Sans, s2.c_str(), White);

	SDL_Texture *Message2 = SDL_CreateTextureFromSurface(renderer, surfaceMessage2);

	rect = new Rect(window, renderer, 200, 300, 1500, 0, 0, 255, 0, 100, Message);
	rect2 = new Rect(window, renderer, 200, 300, 1500, 300, 0, 0, 255, 100, Message2);

	/*Rect* rect = new Rect(window, renderer, 100, 300, 800, 0, 0, 255, 0, 150);
	Rect* rect2 = new Rect(window, renderer, 100, 300, 800, 300, 0, 0, 255, 150);*/

	// while (true)
	// {
	// SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	// cout << 1;
	// }
	// std::cout << "Rects spawned." << std::endl;
	flag = 0;
}

void game::moveRects(SDL_Renderer *renderer)
{
	// SDL_RenderClear(renderer);
	// SDL_RenderPresent(renderer);

	rect->move();
	rect->draw();

	rect2->move();
	rect2->draw();

	if (rect->getx() <= -100)
	{
		flag = 1;
	}
	// std::cout << "Rects moved." << std::endl;
}

void game::drawMathRects(SDL_Renderer *renderer)
{
	if (flag == 1)
	{
		spawnRects(renderer);
	}
	else
		moveRects(renderer);
	// std::cout << "Rects checked." << std::endl;
}

void game::mathRectCollisionDetection(SDL_Renderer *renderer)
{
	SDL_Rect mathRect1 = rect->get_rect();
	SDL_Rect mathRect2 = rect2->get_rect();
	SDL_Rect playerRect = player->getPlayerRect();
	SDL_bool hasIntersection1 = SDL_HasIntersection(&mathRect1, &playerRect);
	SDL_bool hasIntersection2 = SDL_HasIntersection(&mathRect2, &playerRect);
	if (hasIntersection1 == SDL_TRUE && rect->isCollisionDetected == false)
	{
		if (op1 == 0)
			player->set_ammo(player->get_ammo() + ammo1);
		if (op1 == 1)
			player->set_ammo((player->get_ammo() - ammo1));
		if (op1 == 2)
		{
			double temp = (double)player->get_ammo();
			temp *= ammo_mul;
			player->set_ammo((int)temp);
		}
		if (op1 == 3)
			player->set_ammo(player->get_ammo() / ammo1);
		rect->isCollisionDetected = true;
		rect2->isCollisionDetected = true;
	}
	else if (hasIntersection2 == SDL_TRUE && rect2->isCollisionDetected == false)
	{

		if (op2 == 0)
			player->set_ammo(player->get_ammo() + ammo2);
		if (op2 == 1)
			player->set_ammo((player->get_ammo() - ammo2));
		if (op2 == 2)
		{
			double temp = (double)player->get_ammo();
			temp *= ammo_mul;
			player->set_ammo((int)temp);
		}
		if (op2 == 3)
			player->set_ammo(player->get_ammo() / ammo2);
		rect->isCollisionDetected = true;
		rect2->isCollisionDetected = true;
	}
}

void game::outOfAmmo()
{
	std::cout << player->get_ammo() << std::endl;
	if (player->get_ammo() <= 0)
	{
		//clean(audioList);

		// exit(1);
		is_running=false;
	}
}

void game::clean()
{

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	
	SDL_Quit();
	TTF_Quit();
	free(player);
	cout << "Game Cleaned" << endl;
}