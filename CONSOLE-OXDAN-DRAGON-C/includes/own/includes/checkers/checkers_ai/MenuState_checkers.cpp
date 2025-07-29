//
//  MenuState.cpp
//  SDL_Checkers
//
//  Created by Jacky Chiu on 2016-02-29.
//  Copyright © 2016 Jacky Chiu.
//

#include "MenuState_checkers.h"
#include "Texture_checkers.h"
#include "Button_checkers.h"

MenuState_checkers::MenuState_checkers(){
    BUTTON_WIDTH = 346;
    BUTTON_HEIGHT = 40;
    currentStateEnum = MENU_STATE;
    nextStateEnum = MENU_STATE;
    boardButtons = new Button_checkers[FULL_MENU];
    userQuit = false;
    
}

MenuState_checkers::~MenuState_checkers(){
    delete [] boardButtons;
    boardButtons = NULL;
    spriteSheetTexture.free();
    spriteClips.clear();
}

void MenuState_checkers::stateEnter(){
    if (!loadMedia()) {
        //cout<<"Could not load media"<<endl;
        printf("\033[0;31m");
        printf("\n");
        printf("(!ERROR!)");
        printf("\033[0;37m");
        printf(" = ");
        printf("\033[0;32m");
        cout << "(!Could not load media!)\n";
        printf("\033[0;37m");
    }
}

void MenuState_checkers::stateEvent(){
    SDL_Event event;
    
    // Event loop //
    while(SDL_PollEvent(&event)!=0){
        
        // Quits game //
        if(event.type==SDL_QUIT)
        {
            userQuit=true;
        }
        
        if (event.type == SDL_MOUSEMOTION) {
            // Checks if mouse is hovering over a button
            for (int index = 0; index < 3; index ++) {
                if (boardButtons[index].insideButton(346, 40)) {
                    hover[index] = true;
                }
                else {
                    hover[index] = false;
                }
            }
        }
        
        // Checks if a button was clicked
        //if (event.type == SDL_MOUSEBUTTONDOWN) {
            

            nextStateEnum = GAME_STATE;
            GAMEMODE = 1;
            
        //}
    }
}

StateEnum MenuState_checkers::stateUpdate(){
    if (currentStateEnum != nextStateEnum) {
        return nextStateEnum;
    }
    return currentStateEnum;
}

void MenuState_checkers::stateRender(){
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    drawMenu();
    for (int index = 0; index < 3; index++) {
        currentSprite = index;
        if (hover[index]) {
            currentSprite += 3;
        }
        boardButtons[index].render(currentSprite);
    }
}

bool MenuState_checkers::stateExit(){
    return userQuit;
}

bool MenuState_checkers::loadMedia(){
    bool initSuccessfulful = true;
    
    
    // SpriteClips
    // Standard Clips
    SDL_Rect localMultiplayer = {0, 0, 346, 40};
    spriteClips.push_back(localMultiplayer);
    SDL_Rect singlePlayer = {0, 40, 346, 40};
    spriteClips.push_back(singlePlayer);
    SDL_Rect aI = {0, 80, 346, 40};
    spriteClips.push_back(aI);
    // Hover Clips
    SDL_Rect localMultiplayerHover = {346, 0, 346, 40};
    spriteClips.push_back(localMultiplayerHover);
    SDL_Rect singlePlayerHover = {346, 40, 346, 40};
    spriteClips.push_back(singlePlayerHover);
    SDL_Rect aIHover = {346, 80, 346, 40};
    spriteClips.push_back(aIHover);
    // Full Menu
    SDL_Rect fullMenu = {0, 120, 640, 640};
    spriteClips.push_back(fullMenu);
    
    boardButtons[LOCAL_MULTIPLAYER].setPoint(148, 210);
    boardButtons[SINGLEPLAYER].setPoint(148, 280);
    boardButtons[AI_VS_AI].setPoint(148, 350);
    
    return initSuccessfulful;
}

void MenuState_checkers::drawMenu() {
    spriteSheetTexture.render(0, 0, &spriteClips[FULL_MENU]);
}




