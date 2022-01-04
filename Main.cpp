#include "game.h"
#include "TextureManager.h"
#include "Homescreen.h"
int main(int argc, char *args[])
{
	game *g = new game();
	Window* w = new Window();
    Buttons* b = new Buttons();
    Window* win = new Window();
    HighscoreManager* h= new HighscoreManager();
    w->makeWindow("Ammomatics v1.0",1350,650,"images/back_.bmp");
    w->set_button("images/download.bmp",100,520);
    w->set_button("images/instructions.bmp",1100,520);
    w->set_button("images/hs.bmp",1100,0);
    b->mouse_click(g,w);
	return (0);
}