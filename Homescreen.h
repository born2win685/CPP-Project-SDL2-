#pragma once
#ifndef HOMESCREEN_HPP
#define HOMESCREEN_HPP
#include<SDL2/SDL_image.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_timer.h>
#include<iostream>
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
        void makeWindow(const char* name, int w, int h,const char* path);
        void DestroyWindow();
        void set_button(const char* path,int x,int y);
    private:
      SDL_Window* window=NULL;
      SDL_Renderer* renderer=NULL;
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

#endif
