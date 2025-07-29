//
//  ApplicationStateManager.cpp
//  SDL_Checkers
//
//  Created by Jacky Chiu on 2016-02-28.
//  Copyright © 2016 Jacky Chiu. 
//

#include "ApplicationStateManager_checkers.h"
#include "MenuState_checkers.h"
#include "GameState_checkers.h"
#include "GameOverState_checkers.h"

ApplicationStateManager::ApplicationStateManager(){
    currentState = new MenuState_checkers();
    currentState->stateEnter();
}

ApplicationStateManager::~ApplicationStateManager(){
    delete currentState;
    currentState = NULL;
}

void ApplicationStateManager::stateEvent(){
    currentState->stateEvent();
}

StateEnum ApplicationStateManager::stateUpdate(){
    return currentState->stateUpdate();
}

void ApplicationStateManager::stateRender(){
    currentState->stateRender();
}

bool ApplicationStateManager::stateExit(){
    return currentState->stateExit();
}

void ApplicationStateManager::setCurrentStateEnum(StateEnum current){
    currentStateEnum = current;
}

StateEnum ApplicationStateManager::getCurrentStateEnum(){
    return currentStateEnum;
}

void ApplicationStateManager::changeStates(){
    
    delete currentState;
    currentState = NULL;
    
    switch (currentStateEnum) {
        case MENU_STATE:
            currentState = new MenuState_checkers;
            break;
        case GAME_STATE:
            currentState = new GameState_checkers;
            break;
        case GAME_OVER_STATE:
            currentState = new GameOverState;
            break;
        default:
            break;
    }
    currentState->stateEnter();
}