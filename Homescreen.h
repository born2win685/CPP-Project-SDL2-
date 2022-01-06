#pragma once
#ifndef HOMESCREEN_HPP
#define HOMESCREEN_HPP
#include<SDL2/SDL_image.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_timer.h>
#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
#include "game.h"
using namespace std;

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
        void mouse_click(game* g,Window* w);
    private:
        int mx,my;
};

// class Text
// {
//     public:
//         Text(SDL_Renderer *renderer,const string &f_path,int f_size,const string &message,int x,int y,const SDL_Color &color);
//         void display(SDL_Renderer *renderer);
//         static SDL_Texture *loadfont(SDL_Renderer *renderer,const string &f_path,int f_size,const string &message,const SDL_Color &color);
//         ~Text();
//         int rect_w=0,rect_h=0;
//     private:
//         SDL_Texture *texture=nullptr;
//         mutable SDL_Rect Rect;
// };

class HighscoreManager
{
    public:
        string get_username(SDL_Window* win,SDL_Renderer* renderer);
        void add_score(double n);
        void display_score();
    private:
        unordered_map<string,int> score_check;
        unordered_map<int,string> temp_;
        string username;
        string score;
        string highscore;
};

#endif
