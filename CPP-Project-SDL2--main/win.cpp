// #include <stdio.h>
// #include "Homescreen.h"

// int main(int argc, char* args[])
// {
//     Window* w = new Window();
//     w->makeWindow("Game",1250,650);
//     w->set_button("images/download.bmp",100,520);
//     w->set_button("images/instructions.bmp",1100,520);
//     Buttons* b = new Buttons();
//     //flag  work
//     //1     new game
//     //2     instructions
//     //3     high score 
//     b->mouse_click(100,520,201,115,1);
    
//     SDL_Event event;
//     bool quit=true;
//     while(quit)
//     {
//         while(SDL_PollEvent(&event)!=0)
//         {

//         if(event.type == SDL_QUIT)
//             quit=false;
//         }
//     }

//     return 0;
// }