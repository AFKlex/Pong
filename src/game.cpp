//
// Created by afklex on 10/20/23.
//

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include "header/game.h"
#include<iostream>
const int WIDTH = 640;
const int HEIGHT = 480;

Ball::Ball(int x ,int y){
    this->x = x;
    this->y = y;
    this->velocity=10;
    this->ball_rect = SDL_Rect {this->x,this->y, 32, 32 };

    this->directionX = 1;
    this->directionY = 1;

}

void Ball::setImage(SDL_Renderer *&ptrRenderer, SDL_Texture *&ptrTexture) {
    this->ballImage = ptrTexture;
}

SDL_Rect* Ball::getRect() {
    return &ball_rect;
}

void Ball::moveBall(){
    //std::cout << "X: " << x << "Y: " << this->y << std::endl;
    this->x += this->directionX * this->velocity;
    this->y += this->directionY * this->velocity;
    ball_rect.x = this->x;
    ball_rect.y = this->y;
    borderCollision();
}

void Ball::borderCollision(){
    // Reflect the ball at x collision
    if(x+ball_rect.w >= WIDTH || x <=0){
        directionX *=-1;
    }
    // reflect the ball at y collision
    if(y+ball_rect.h >= HEIGHT || y<= 0){
        directionY *=-1;
    }

}



