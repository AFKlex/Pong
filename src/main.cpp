//
// Created by afklex on 10/20/23.
//
#include<iostream>
#include"header/window.h"
#include"header/game.h"

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


    SDL_Texture* ballImage = loadTexture("../assets/ball.png", renderer);
    Ball ball= Ball(288,208);

    ball.setImage(ballImage);

    SDL_Texture* playerImage = loadTexture("../assets/player.png", renderer);
    Player player1 = Player(20, 200);
    Player player2 = Player(600, 200);

    bool quit = false;
    SDL_Event e;

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

        SDL_RenderCopy(renderer,ballImage, nullptr, ball.getRect() );
        SDL_RenderCopy(renderer,playerImage, nullptr, player1.getRect() );
        SDL_RenderCopy(renderer,playerImage, nullptr, player2.getRect() );

        SDL_RenderPresent(renderer);
        SDL_Delay(1000/60);
    }

    // Free all things from the endless suffering that is my game.
    destroyGame(window,mainSurface,renderer);
    return 0;
}