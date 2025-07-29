//
//  Button.cpp
//  SDL_Checkers
//
//  Created by Jacky Chiu on 2016-02-13.
//  Copyright © 2016 Jacky Chiu. 
//

#include "Button_checkers.h"
#include "GameState_checkers.h"
#include "Texture_checkers.h"
#include "Application_checkers.h"

Button_checkers::Button_checkers(){
    buttonPoint.x = 0;
    buttonPoint.y = 0;
}

Button_checkers::~Button_checkers(){
    buttonPoint.x = NULL;
    buttonPoint.y = NULL;
}

void Button_checkers::setPoint(int x, int y){
    buttonPoint.x = x;
    buttonPoint.y = y;
}

void Button_checkers::render(int sprite){
    //Render button with spritesheet
    spriteSheetTexture.render(buttonPoint.x, buttonPoint.y, &spriteClips[sprite]);
}

bool Button_checkers::insideButton(int buttonWidth, int buttonHeight){

    int x,y;
    bool insideButton = true;
    SDL_GetMouseState(&x,&y);
    
    // Above button //
    if(y < buttonPoint.y){
        insideButton = false;
    }
    // Under button //
    else if (y > buttonPoint.y + buttonHeight){
        insideButton = false;
    }
    // Left of button //
    else if (x < buttonPoint.x) {
        insideButton = false;
    }
    // Right of button //
    else if (x > buttonPoint.x + buttonWidth){
        insideButton = false;
    }

    return insideButton;
}

int Button_checkers::getButtonPointX(){
    return buttonPoint.x;
}

int Button_checkers::getButtonPointY(){
    return buttonPoint.y;
}