#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>


const int HEIGHT = 800, WIDTH = 800;
int main(void)
{


    // attempt to initialize graphics and timer system
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("Our Chess Board",
                                       SDL_WINDOWPOS_CENTERED ,
                                       SDL_WINDOWPOS_CENTERED ,
                                       HEIGHT, WIDTH,
                                       0);

    // create a renderer, which sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);



    // load the image into memory using SDL_image library function
    SDL_Surface* surface = IMG_Load("resources/board.jpg");
    SDL_Surface* guti = IMG_Load("resources/hello2.png");


    // load the image data into the graphics hardware's memory
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_Texture* tex2 = SDL_CreateTextureFromSurface(rend, guti);



    SDL_FreeSurface(surface);
    SDL_FreeSurface(guti);

    // struct to hold the position and size of the sprite
    SDL_Rect src, dest;

    // get the dimensions of texture
    SDL_QueryTexture(tex2, NULL, NULL, &src.w, &src.h);

    // position the sprite at the bottom center of the window
    // origin is the top left corner, positive y is down
    dest.x = 0;
    dest.y = 0;
    dest.w = 100;
    dest.h = 100;

    src.x = 0;
    src.y = 0;

    // clear the window
    SDL_RenderClear(rend);

    // draw the image to the window
    SDL_RenderCopy(rend, tex, NULL, NULL);
    SDL_RenderCopy(rend, tex2, &src, &dest);

    //SDL_RenderCopy(rend, tex2, NULL, NULL);
    SDL_RenderPresent(rend);

    // wait a few seconds
    SDL_Delay(5000);

    // clean up resources before exiting
    SDL_DestroyTexture(tex);
    SDL_DestroyTexture(tex2);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();

}