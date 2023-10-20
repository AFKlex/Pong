//
// Created by afklex on 10/20/23.
//
#include<iostream>
#include"header/window.h"
int main(){
    std::cout << "Hello World" << std::endl;

    SDL_Window *window = nullptr;
    if(!initGame(window)){
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


    return 0;
}