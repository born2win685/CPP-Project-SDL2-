#include <stdio.h>
#include "Homescreen.h"

int main(int argc, char* args[])
{
    Window* w = new Window();
    Buttons* b = new Buttons();
    Window* win = new Window();
    HighscoreManager* h= new HighscoreManager();
    w->makeWindow("Ammomatics v1.0",1350,650,"images/back.bmp");
    w->set_button("images/download.bmp",100,520);
    w->set_button("images/instructions.bmp",1100,520);
    w->set_button("images/hs.bmp",1100,0);
    b->mouse_click();
    w->DestroyWindow();    
    win->makeWindow("Game over",1350,650,"images/back.bmp");
    h->get_username(win->window,win->renderer);
    win->DestroyWindow();
    h->add_score(46906);   
    return 0;
}