//
// Created by afklex on 10/20/23.
//
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<SDL2/SDL_ttf.h>
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

bool initRenderer(SDL_Renderer *&ptrRenderer, SDL_Window *&ptrWindow){
    bool success = true;
    ptrRenderer = SDL_CreateRenderer(ptrWindow, -1, SDL_RENDERER_ACCELERATED);
    if (ptrRenderer == nullptr) {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    return  success;
}

bool initFont(SDL_Surface *&ptrMessage, TTF_Font *&ptrFont){
    bool  success = true;
    if( TTF_Init() == -1 ){ //Initialize SDL_ttf
        std::cout << "Failed to load Font" << std::endl;
        success = false;
    }
    ptrFont = TTF_OpenFont("../assets/Gothic.ttf", 100);
    if(ptrFont == nullptr){
        std::cout << "Failed to load Font! TTF_Error: " << TTF_GetError() << std::endl;
        success = false;
    }

    return success;
}

bool initGame(SDL_Window *&ptrWindow, SDL_Surface *&ptrSurface, SDL_Renderer *&ptrRenderer, SDL_Surface*& ptrMessage, TTF_Font *& ptrFont){
    bool  success = true;

    if(SDL_Init(SDL_INIT_VIDEO) <0){
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        success = false;
    }else{
        success = initWindow(ptrWindow);
    }
    if(success){
        ptrSurface  = SDL_GetWindowSurface(ptrWindow);
    }else{
        std::cout << "Failed to Load ptrSurface because Window was not good! SDL Error: " << SDL_GetError() << std::endl;
    }

    if(!initFont(ptrMessage,ptrFont)){
        std::cout << "Failed to load Font! SDL Error: " << SDL_GetError() << TTF_GetError() << std::endl;
    }

    if(!initRenderer(ptrRenderer,ptrWindow)){
        std::cout << "Failed to load ptrRenderer! SDL Error: " << SDL_GetError() << std::endl;
    }

    return success;
}

void destroyGame(SDL_Window *&ptrWindow, SDL_Surface *&ptrSurface, SDL_Renderer *&ptrRenderer){
    SDL_DestroyWindow(ptrWindow);
    SDL_DestroyRenderer(ptrRenderer);
    ptrWindow = nullptr;
    ptrRenderer = nullptr;
    ptrSurface = nullptr;
    SDL_Quit();
}

SDL_Texture *loadTexture(const std::string &path, SDL_Renderer *&ptrRenderer){
    SDL_Texture* newTexture = nullptr;

    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == nullptr){
        std::cout << "Unable to Load Image: " << IMG_GetError() << std::endl;
    }else{
        newTexture = SDL_CreateTextureFromSurface(ptrRenderer,loadedSurface);
    }
    if(newTexture == nullptr){
        std::cout << "Unable to Load Texture: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(loadedSurface);

    return  newTexture;

}

void setBackgroundColor(SDL_Renderer *&ptrRenderer){
    SDL_SetRenderDrawColor(ptrRenderer, 176,179,181, 255 );
    SDL_RenderClear(ptrRenderer);

}

void drawGrid(SDL_Renderer *&ptrRenderer){


    // That big dumb i want to fill some square
    /*for(int i=0; i<= WIDTH; i+=10){
        SDL_RenderDrawLine( ptrRenderer, i, 0, i, HEIGHT);
    }

    for(int i=0; i<= HEIGHT; i+=10){
        SDL_RenderDrawLine( ptrRenderer, 0, i, WIDTH, i);
    }*/
    int rowCounter = 0;
    for(int i = 0; i<=WIDTH; i+=20) {
        for (int j = 0; j <= HEIGHT; j += 20) {
            rowCounter++;
            SDL_Rect rect;
            rect = {i, j, 20, 20};
            if(rowCounter %2 != 0){
                //fillRect.x = 0; fillRect.y = 0;
                SDL_SetRenderDrawColor(ptrRenderer,184,185, 186, 255);
                SDL_RenderFillRect(ptrRenderer,&rect);

            }
            //SDL_SetRenderDrawColor(ptrRenderer, 0, 0, 0, 0xFF );
            //SDL_RenderDrawRect(ptrRenderer, &rect);
        }
    }
}

SDL_Texture* loadTextTexture(SDL_Renderer *& ptrRenderer, SDL_Texture *&ptrTexture, TTF_Font *& ptrFont, const std::string& stringToDraw, SDL_Color colorOfString ){
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(ptrFont, stringToDraw.c_str(), colorOfString);
    if(surfaceMessage == nullptr){
        std::cout << "Failed to load SurfaceMessage! SDL_Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    if(ptrTexture != nullptr){
        SDL_DestroyTexture(ptrTexture);
    }
    ptrTexture = SDL_CreateTextureFromSurface(ptrRenderer, surfaceMessage);

    if(ptrTexture == nullptr){
        std::cout << "Failed to load Message! SDL_Error: " << SDL_GetError() << std::endl;
    }else{
        free(surfaceMessage);
    }

    return  ptrTexture;

}



