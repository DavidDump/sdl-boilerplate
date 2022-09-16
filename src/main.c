#include <stdio.h>

#ifdef LINUX
#include <SDL2/SDL.h> // usr/include/SDL2
#endif

#ifdef _WIN32
#define SDL_MAIN_HANDLED
#include "SDL.h"
#endif

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define BG_COLOR 0x6080FFFF

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))
#define COLOR_R(x) ((x>>(8*3)) & 255)
#define COLOR_G(x) ((x>>(8*2)) & 255)
#define COLOR_B(x) ((x>>(8*1)) & 255)
#define COLOR_A(x) ((x>>(8*0)) & 255)

int main(int argc, char** argv){
    SDL_Renderer *renderer;
    SDL_Window *window;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL init failed.\n");
        exit(1);
    }
    
    SDL_DisplayMode monitor;
    SDL_GetCurrentDisplayMode(0, &monitor);
    window = SDL_CreateWindow("Hello, World!", monitor.w / 2 - WINDOW_WIDTH / 2, monitor.h / 2 - WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if(!window){
        printf("SDL window creaton failed.\n");
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer){
        printf("SDL renderer creaton failed.\n");
        exit(1);
    }

    SDL_Vertex cubeVerts[] = {
        {.position = {.x = WINDOW_WIDTH * 0.25, .y = WINDOW_HEIGHT * 0.25}, .color = {.r = 255, .g = 0, .b = 0, .a = SDL_ALPHA_OPAQUE}},
        {.position = {.x = WINDOW_WIDTH * 0.75, .y = WINDOW_HEIGHT * 0.25}, .color = {.r = 0, .g = 255, .b = 0, .a = SDL_ALPHA_OPAQUE}},
        {.position = {.x = WINDOW_WIDTH * 0.25, .y = WINDOW_HEIGHT * 0.75}, .color = {.r = 0, .g = 0, .b = 255, .a = SDL_ALPHA_OPAQUE}},
        {.position = {.x = WINDOW_WIDTH * 0.75, .y = WINDOW_HEIGHT * 0.75}, .color = {.r = 0, .g = 0, .b = 0, .a = SDL_ALPHA_OPAQUE}},
    };
    
    int cubeIndicies[] = {
        0, 1, 2,
        2, 3, 1
    };

    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 last = 0;
    double deltaTime = 0;
    int running = 1;
    while(running){
        // Clear the screen
        SDL_SetRenderDrawColor(renderer, COLOR_R(BG_COLOR), COLOR_G(BG_COLOR), COLOR_B(BG_COLOR), COLOR_A(BG_COLOR));
        SDL_RenderClear(renderer);
        
        // Delta time
        last = now;
        now = SDL_GetPerformanceCounter();
        deltaTime = (double)((now - last)*1000 / (double)SDL_GetPerformanceFrequency());
        (void)deltaTime;


        // Event handling
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = 0;
                    break;
                default:
                    break;
            }
        }

        //Setting the actual draw color.
        // SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        SDL_RenderGeometry(renderer, NULL, cubeVerts, ARRAY_SIZE(cubeVerts), cubeIndicies, ARRAY_SIZE(cubeIndicies));

        // Render screen
        SDL_RenderPresent(renderer);
        // SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}