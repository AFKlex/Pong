//
// Created by afklex on 10/20/23.
//

#ifndef PONG_GAME_H
#define PONG_GAME_H
class Ball{
public:
    SDL_Texture *ballImage = nullptr;
    SDL_Rect ball_rect{};
    int x;
    int y;
    int velocity;

    Ball(int x,int y);
    void setImage(SDL_Renderer *&ptrRenderer, SDL_Texture *&ptrTexture);
    SDL_Rect* getRect();
    void moveBall();
private:
    void borderCollision();
    int directionX;
    int directionY;


};
#endif //PONG_GAME_H
