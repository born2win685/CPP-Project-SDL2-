#include "Homescreen.h"

void Window::makeWindow(const char* title, int width, int height,const char* path)
{
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0)
    {
        cout<<"error: Failed to initialize "<< SDL_GetError()<<endl;    
    }
    window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,0 ,width,height,0);
    
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
                k->makeWindow("Instructions-click anywhere to close",715,722,"images/i.bmp");
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
            {
              Window* q= new Window();
              q->makeWindow("High Score-click anywhere to close",715,722,"images/i.bmp");
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
                q->DestroyWindow();
            }    
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

void HighscoreManager::get_username(SDL_Window* window,SDL_Renderer* ren)
{
        SDL_Color colour={255,0,0,255};
        Text t(ren,"font.ttf",30,"Enter name",colour);
        t.display(100,100,ren);
        SDL_UpdateWindowSurface(window);
        bool quit=true;
        SDL_Event e;
        SDL_StartTextInput();
        while(quit)
        {
            while(SDL_PollEvent(&e))
            {
                if(e.type==SDL_QUIT)
                    quit= false;
                else if(e.type==SDL_TEXTINPUT || e.type==SDL_KEYDOWN)
                {
                    system("clear");
                    if(e.type==SDL_KEYDOWN && e.key.keysym.sym==SDLK_BACKSPACE && username.length()>0)
                        username.pop_back();
                    else if(e.type==SDL_TEXTINPUT)
                        username+=e.text.text;
                }                
            }
        }
        SDL_StopTextInput();
}

void HighscoreManager::add_score()
{
    fstream f("score.txt",ios::out | ios::app);
    if(f.is_open())
    {
        for(int i=0; i<username.size(); i++)
            f.put(username.at(i));
        f.put('\n');
        f.close();
    }


}

SDL_Texture *Text::loadfont(SDL_Renderer *renderer, const string &f_path,int f_size,const string &message_text,const SDL_Color &color)
{
    TTF_Font *font = TTF_OpenFont(f_path.c_str(),f_size);
    auto text_surface=TTF_RenderText_Solid(font,message_text.c_str(),color);
    auto text_texture=SDL_CreateTextureFromSurface(renderer,text_surface);
    SDL_FreeSurface(text_surface);
    return text_texture;
}

void Text::display(int x,int y,SDL_Renderer *renderer)const
{
    Rect.x=x;
    Rect.y=y;
    SDL_RenderCopy(renderer,texture,nullptr,&Rect);
}

Text::Text(SDL_Renderer *renderer,const string &f_path,int f_size,const string &message,const SDL_Color &color)
{
    texture= loadfont(renderer,f_path,f_size,message,color);
    SDL_QueryTexture(texture,nullptr,nullptr,&Rect.w,&Rect.h);
}
