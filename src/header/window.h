//
// Created by afklex on 10/20/23.
//
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>

#ifndef PONG_WINDOW_H
#define PONG_WINDOW_H
bool initGame(SDL_Window *&ptrWindow, SDL_Surface *&ptrSurface, SDL_Renderer *&ptrRenderer);
void destroyGame(SDL_Window *&ptrWindow, SDL_Surface *&ptrSurface, SDL_Renderer *&ptrRenderer);
void drawGrid(SDL_Renderer *&ptrRenderer);
void setBackgroundColor(SDL_Renderer *&ptrRenderer);
SDL_Texture *loadTexture(const std::string &path, SDL_Renderer *&ptrRenderer);
#endif //PONG_WINDOW_H
