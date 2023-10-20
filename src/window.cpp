//
// Created by afklex on 10/20/23.
//
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
const int WIDTH = 640;
const int HEIGHT = 480;

bool initWindow(SDL_Window *&ptrWindow){
    bool  success = true;

    // Initialize Window
    ptrWindow = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,WIDTH,HEIGHT,SDL_WINDOW_SHOWN);
    if(ptrWindow == nullptr){
        std::cout << "Window Could not be loaded! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    return success;
}

bool initGame(SDL_Window *&ptrWindow){
    bool  success = true;

    if(SDL_Init(SDL_INIT_VIDEO) <0){
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        success = false;
    }else{
        success = initWindow(ptrWindow);
    }

    return success;
}


