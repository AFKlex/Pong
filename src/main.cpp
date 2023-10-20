//
// Created by afklex on 10/20/23.
//
#include<iostream>
#include"header/window.h"
int main(){
    // The Game window
    SDL_Window *window = nullptr;

    // Surface where Stuff happens
    SDL_Surface *mainSurface = nullptr;

    // Renderer for Drawing
    SDL_Renderer *renderer = nullptr;


    if(!initGame(window, mainSurface, renderer)){
        std::cout << "Failed to Init Game!" << std::endl;
    }

    bool quit = false;
    SDL_Event e;

    while (!quit){
        while (SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = true;
            }
        }
        SDL_Delay(10);
    }

    // Free all things from the endless suffering that is my game.
    destroyGame(window,mainSurface,renderer);
    return 0;
}