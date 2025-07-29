//
//  GameOverState.cpp
//  SDL_Checkers
//
//  Created by Jacky Chiu on 2016-03-23.
//  Copyright © 2016 Jacky Chiu.
//
#include <stdio.h>
#include "GameOverState_checkers.h"
#include "Texture_checkers.h"

GameOverState::GameOverState(){
    currentStateEnum = GAME_OVER_STATE;
    nextStateEnum = GAME_OVER_STATE;
    userQuit = false;
}

GameOverState::~GameOverState(){

}

void GameOverState::stateEnter(){
    printf("\033[0;31m!GAME OVER!\n \033[0;37m");
}

void GameOverState::stateEvent(){
    SDL_Event event;
    // Event loop //
    while(SDL_PollEvent(&event)!=0){

        // Quits game //
        if(event.type==SDL_QUIT)
        {
            userQuit=true;
        }
    }
}

StateEnum GameOverState::stateUpdate(){
    if (currentStateEnum != nextStateEnum) {
        return nextStateEnum;
    }
    return currentStateEnum;
}

void GameOverState::stateRender(){
    // Light wood color //
    SDL_SetRenderDrawColor(gRenderer, 0xD4, 0x9A, 0x6A, 0xFF);
    // Refreshs screen //
    SDL_RenderClear(gRenderer);
}

bool GameOverState::stateExit(){
    return userQuit;
}

bool GameOverState::loadMedia(){
    return false;
}
