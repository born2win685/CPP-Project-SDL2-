#include "Homescreen.h"

void Window::makeWindow(const char* title, int width, int height,const char* path)
{
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0)
    {
        cout<<"error: Failed to initialize "<< SDL_GetError()<<endl;    
    }
    window = SDL_CreateWindow(title,0 , 0 ,width,height,0);
    
    if(window==NULL)
            cout<<"Couldn't create window.   error"<< SDL_GetError() << endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer==NULL)
		{
			cout <<"Couldn't create renderer. error"<< SDL_GetError() << endl;
		}

    surface=SDL_GetWindowSurface(window);
    SDL_Rect dest;
    dest.x=0;
    dest.y=100;
    bg_image=SDL_LoadBMP(path);
    SDL_BlitSurface(bg_image, NULL,surface,&dest);
    SDL_UpdateWindowSurface(window);
}

Window::~Window()
{

}

Window::Window()
{
    
}

void Window::set_button(const char* path,int p_x,int p_y)
{
    surface=SDL_GetWindowSurface(Window::window);
    button=SDL_LoadBMP(path);
    SDL_Rect dest;
    dest.x = p_x;
    dest.y = p_y;
    int result = SDL_BlitSurface(button,NULL,surface,&dest);
    if ( result < 0 ) 
	 cout<<"blit failed"<<endl;
    SDL_UpdateWindowSurface(window);

}

void Window::DestroyWindow()
{
    SDL_DestroyWindow(window);
}


void Buttons::mouse_click()
{
    SDL_Event mouse_event;
    bool quit =true;
    while(quit)
    {
    while(SDL_PollEvent(&mouse_event))
    {
    switch(mouse_event.type)
    {
        case SDL_QUIT: 
            quit =false; 
            break;
        case SDL_MOUSEBUTTONDOWN: 
        {
            mx=mouse_event.motion.x;
            my=mouse_event.motion.y;
            if(mx>100 && mx<301 && my<635 && my>520)  
                cout<<"clicked"<<endl;
            if(mx>1100 && mx<1205 && my<635 && my>520)  
            {
                cout<<"instructions"<<endl;
                Window* k= new Window();
                k->makeWindow("instructions",1250,650,"/home/born2win685/Desktop/cpp_project/images/bg.bmp");
                SDL_Event event;
                bool quit=true;
                while(quit)
                {
                    while(SDL_PollEvent(&event)!=0)
                    {
                        if(event.type == SDL_MOUSEBUTTONDOWN)
                            quit=false;
                    }
                }
                cout<<"done"<<endl;
                k->DestroyWindow();
            }
            if(mx>1100 && mx<1200 && my<100 && my>0)
                cout<<"high score"<<endl;
            break;
            default:
                break;
        }                
                       
    }
                   
    }
    }
}    
    


Buttons::Buttons()
{

}

Buttons::~Buttons()
{

}
