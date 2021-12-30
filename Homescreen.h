#pragma once
#ifndef HOMESCREEN_HPP
#define HOMESCREEN_HPP
#include<SDL2/SDL_image.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_timer.h>
#include<iostream>
#include<fstream>
using namespace std;

class Score
{
    public:
        void add_score(const char* score);
        void display_score(const  char* score);
    private:
        const char* score;
};



class Window 
{
    public:
        Window();
        ~Window();
        SDL_Window* window=NULL;
        SDL_Renderer* renderer=NULL;
        void makeWindow(const char* name, int w, int h,const char* path);
        void DestroyWindow();
        void set_button(const char* path,int x,int y);
    private:    
      SDL_Surface* surface=NULL;
      SDL_Surface* bg_image=NULL;
      SDL_Surface* button=NULL;
};

class Buttons
{
    public:
        Buttons();
        ~Buttons();
        void mouse_click();
    private:
        int mx,my;
};

class Text
{
    public:
        Text(SDL_Renderer *renderer,const string &f_path,int f_size,const string &message,const SDL_Color &color);
        void display(int x,int y,SDL_Renderer *renderer)const;
        static SDL_Texture *loadfont(SDL_Renderer *renderer,const string &f_path,int f_size,const string &message,const SDL_Color &color);
    private:
        SDL_Texture *texture=nullptr;
        mutable SDL_Rect Rect;
};

class HighscoreManager
{
    public:
        void get_username(SDL_Window* win,SDL_Renderer* renderer);
        void add_score();
        bool check_highscore();
    private:
        string username;
        const char* score;
        const char* highscore;
};

#endif
