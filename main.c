#include <stdio.h>
#include <SDL2/SDL.h> // usr/include/SDL2

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(){
    SDL_Renderer *renderer;
    SDL_Window *window;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL init failed.\n");
        exit(1);
    }

    window = SDL_CreateWindow("Hello, World!", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if(!window){
        printf("SDL window creaton failed.\n");
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer){
        printf("SDL renderer creaton failed.\n");
        exit(1);
    }

    while(1){
        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
        SDL_RenderClear(renderer);
        
        // Event handling
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    exit(0);
                    break;
                default:
                    break;
            }
        }

        //Setting the actual draw color.
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        SDL_RenderDrawLine(renderer, WINDOW_WIDTH / 2, 0, 0, WINDOW_HEIGHT * 0.9);
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH / 2, 0, WINDOW_WIDTH, WINDOW_HEIGHT * 0.9);
        SDL_RenderDrawLine(renderer, 0, WINDOW_HEIGHT * 0.9, WINDOW_WIDTH, WINDOW_HEIGHT * 0.9);


        // Render screen
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
}