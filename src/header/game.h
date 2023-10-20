//
// Created by afklex on 10/20/23.
//

#ifndef PONG_GAME_H
#define PONG_GAME_H
class Ball{
public:
    SDL_Texture *ballImage = nullptr;
    SDL_Rect ball_rect{};
    int velocity;
    int score_left;
    int score_right;
    Uint32 collisionDelayEndTime;

    Ball(int x,int y);
    void setImage(SDL_Texture *&ptrTexture);
    SDL_Rect* getRect();
    void moveBall();
    void playerCollision(SDL_Rect player);
private:
    void borderCollision();
    int directionX;
    int directionY;
    void resetBall();

};

class Player{
public:

    int velocity;
    int direction;
    bool isMoving;
    SDL_Rect playerRect{};

    Player(int x, int y);
    SDL_Rect* getRect();
    SDL_Rect getRectData();
    void changeMoving(bool changeTo);
    void changeUP();
    void changeDown();
    void movePlayer();
};


#endif //PONG_GAME_// H
