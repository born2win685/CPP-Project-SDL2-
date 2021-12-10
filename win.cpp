#include <stdio.h>
#include "Homescreen.h"

int main(int argc, char* args[])
{
    Window* w = new Window();
    w->makeWindow("Ammomatics v1.0",1250,650,"/home/born2win685/Desktop/cpp_project/images/back.bmp");
    w->set_button("/home/born2win685/Desktop/cpp_project/images/download.bmp",100,520);
    w->set_button("/home/born2win685/Desktop/cpp_project/images/instructions.bmp",1100,520);
    w->set_button("/home/born2win685/Desktop/cpp_project/images/hs.bmp",1100,0);

    Buttons* b = new Buttons();
    b->mouse_click();
    w->DestroyWindow();
    return 0;
}
