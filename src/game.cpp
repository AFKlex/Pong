//
// Created by afklex on 10/20/23.
//

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include "header/game.h"
#include<iostream>
#include<cstdlib>
#include<ctime>

const int WIDTH = 640;
const int HEIGHT = 480;

int generate_random_number(int min, int max){
    std::srand(std::time(nullptr)); // use current time as seed for random generator

    int random_variable = std::rand() % (max-min) + min;//Max is not included in the range while min is.
    return random_variable;
}

Ball::Ball(int x ,int y){

    this->velocity=1;
    this->ball_rect = SDL_Rect {x,y, 32, 32 };
    collisionDelayEndTime= 0;
    this->directionX = 1;
    this->directionY = 1;

}

void Ball::setImage(SDL_Texture *&ptrTexture) {
    this->ballImage = ptrTexture;
}

SDL_Rect* Ball::getRect() {
    return &ball_rect;
}

void Ball::moveBall(){
    //std::cout << "X: " << x << "Y: " << this->y << std::endl;
    ball_rect.x += this->directionX * this->velocity;
    ball_rect.y += this->directionY * this->velocity;

    borderCollision();
}

void Ball::resetBall() {
    ball_rect.x = WIDTH/2-ball_rect.w;
    ball_rect.y = HEIGHT/2-ball_rect.h;
    std::cout << " x: " <<  WIDTH/2-ball_rect.w << " y: " << HEIGHT/2-ball_rect.h << std::endl;
}

void Ball::borderCollision(){
    // Reflect the ball at x collision
    if(ball_rect.x +ball_rect.w >= WIDTH){
        directionX *=-1;
        score_left++;
        resetBall();
        velocity= 2;

        std::cout << "Score Left: " << score_left << " Score Right: " << score_right << std::endl;
    }else if(ball_rect.x <=0){
        directionX *=-1;
        score_right++;
        resetBall();
        velocity = 2;

        std::cout << "Score Left: " << score_left << " Score Right: " << score_right << std::endl;
    }

    if(ball_rect.y +ball_rect.h >= HEIGHT || ball_rect.y<= 0){
        directionY *=-1;
    }

}


void Ball::playerCollision(SDL_Rect player) {
    static bool collisionDelay = false;  // Static variable to track the collision delay
    Uint32 currentTime = SDL_GetTicks();  // Current time
    int randomInt = 0;

    // Check if the collision delay has elapsed
    if (collisionDelay && currentTime >= collisionDelayEndTime) {
        collisionDelay = false;  // Reset the collision delay flag
    }

    if(!collisionDelay) {
        if ((ball_rect.x <= player.x + player.w && player.x < WIDTH / 2) ||
            (ball_rect.x + ball_rect.w >= player.x && player.x > WIDTH / 2)) {

            if (!(ball_rect.y + ball_rect.h <= player.y || ball_rect.y >= player.y + player.h)) {

                randomInt = generate_random_number(0,4);
                std::cout<< randomInt <<std::endl;

                switch (randomInt) {
                    case 0:
                        if(directionY >0){
                            directionY = 2;
                        } else{
                            directionY = -2;
                        }
                        break;
                    case 1:
                        if(directionX > 0){
                            directionX = 2;
                        }else{
                            directionX = -2;
                        }
                        break;
                    case 2:
                        if(directionX > 0){
                            directionX =1;
                        }else{
                            directionX = -1;
                        }
                        break;
                    case 3:
                        if(directionY >0){
                            directionY = 1;
                        } else{
                            directionY = -1;
                        }
                }
                directionX *= -1;
                std::cout << "Current direction: " << directionX << ", " << directionY << std::endl;

                collisionDelay = true;  // Set the collision delay flag
                collisionDelayEndTime = currentTime + 500;
                if(velocity <=6){
                    velocity++;
                }
            }

        }
    }
}

Player::Player(int x, int y) {
    velocity = 10;
    direction= 1;
    isMoving = false;
    playerRect = SDL_Rect {x,y, 10*2, 32*3 };
    std::cout << playerRect.x << std::endl;

}

SDL_Rect* Player::getRect() {
    return &playerRect;
}

SDL_Rect Player::getRectData() {
    return playerRect;
}

void Player::movePlayer() {
    if(isMoving){
        if(playerRect.y < 0) { // Stop at Top
            playerRect.y +=1;
        }else if(playerRect.y + playerRect.h > HEIGHT){ // Stop at bottom
            playerRect.y -=1;
        }else{
            playerRect.y += direction*velocity; // Move player
        }

    }
}

void Player::changeUP() {
    direction  = -1;
}
void Player::changeDown() {
    direction = 1;
}

void Player::changeMoving(bool changeTo){
    isMoving = changeTo;
}

