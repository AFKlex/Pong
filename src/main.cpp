//
// Created by afklex on 10/20/23.
//
#include<iostream>
#include"header/window.h"
#include"header/game.h"
#include<SDL2/SDL_ttf.h>

int main(){
    // The Game window
    SDL_Window *window = nullptr;

    // Surface where Stuff happens
    SDL_Surface *mainSurface = nullptr;

    // Renderer for Drawing
    SDL_Renderer *renderer = nullptr;

    SDL_Surface* message = nullptr;
    SDL_Texture* messageTexture = nullptr;
    TTF_Font *font = nullptr;
    int scoreLeft = 0;
    int scoreRight = 0;



    if(!initGame(window, mainSurface, renderer, message, font)){
        std::cout << "Failed to Init Game!" << std::endl;
    }


    SDL_Texture* ballImage = loadTexture("../assets/ball.png", renderer);
    Ball ball= Ball(288,208);

    ball.setImage(ballImage);

    SDL_Texture* playerImage = loadTexture("../assets/player.png", renderer);
    Player player1 = Player(20, 200);
    Player player2 = Player(600, 200);

    bool quit = false;
    SDL_Event e;


    SDL_Color textColor ={255,255,255};






    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 640/2-50;  //controls the rect's x coordinate
    Message_rect.y = 10; // controls the rect's y coordinte
    Message_rect.w = 100; // controls the width of the rect
    Message_rect.h = 100;

    TTF_SetFontHinting(font, TTF_HINTING_NORMAL);
    while (!quit){
        while (SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = true;
            }else if (e.type == SDL_KEYDOWN) {
                //Select surfaces based on key press
                switch (e.key.keysym.sym) {

                    case SDLK_w:
                        player1.changeUP();
                        player1.changeMoving(true);
                        break;
                    case SDLK_s:
                        player1.changeDown();
                        player1.changeMoving(true);
                        break;
                    case SDLK_DOWN:
                        player2.changeDown();
                        player2.changeMoving(true);
                        break;
                    case SDLK_UP:
                        player2.changeUP();
                        player2.changeMoving(true);
                        break;
                    case SDLK_SPACE:
                        ball.changeActivity(true);

                }
            }else if(e.type == SDL_KEYUP){
                switch(e.key.keysym.sym){
                    case SDLK_w:
                    case SDLK_s:
                        player1.changeMoving(false);
                        break;
                    case SDLK_DOWN:
                    case SDLK_UP:
                        player2.changeMoving(false);
                        break;
                }

            }
        }
        player1.movePlayer();
        player2.movePlayer();
        setBackgroundColor(renderer);
        drawGrid(renderer);
        ball.moveBall();
        ball.playerCollision(player1.getRectData());
        ball.playerCollision(player2.getRectData());

        if(scoreLeft < ball.score_left || scoreRight < ball.score_right) {
            //std::cout<< "render new text" << std::endl;
            scoreLeft = ball.score_left;
            scoreRight = ball.score_right;
            std::string messageText = std::to_string(ball.score_left) + ":" + std::to_string(ball.score_right);
            loadTextTexture(renderer, messageTexture, font, messageText, textColor);
        }
        SDL_RenderCopy(renderer,ballImage, nullptr, ball.getRect() );
        SDL_RenderCopy(renderer,playerImage, nullptr, player1.getRect() );
        SDL_RenderCopy(renderer,playerImage, nullptr, player2.getRect() );
        SDL_RenderCopy(renderer, messageTexture, nullptr, &Message_rect);



        SDL_RenderPresent(renderer);
        SDL_Delay(1000/60);
    }

    // Free all things from the endless suffering that is my game.
    destroyGame(window,mainSurface,renderer);
    free(message);
    SDL_DestroyTexture(messageTexture);
    SDL_DestroyTexture(ballImage);
    SDL_DestroyTexture(playerImage);

    return 0;
}