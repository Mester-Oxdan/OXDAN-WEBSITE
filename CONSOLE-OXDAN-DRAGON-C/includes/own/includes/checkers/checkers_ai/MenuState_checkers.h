//
//  MenuState.h
//  SDL_Checkers
//
//  Created by Jacky Chiu on 2016-02-29.
//  Copyright © 2016 Jacky Chiu.
//

#ifndef MenuState_h
#define MenuState_h

#ifdef _WIN32
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#endif

#ifdef __linux
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#include "ApplicationState_checkers.h"
#include "Application_checkers.h"

class Button_checkers;

enum MenuSpriteEnum {
    LOCAL_MULTIPLAYER,
    SINGLEPLAYER,
    AI_VS_AI,
    LOCAL_MULTIPLAYER_HOVER,
    SINGLEPLAYER_HOVER,
    AI_VS_AI_HOVER,
    FULL_MENU
};


class MenuState_checkers : public ApplicationState {
public:
    MenuState_checkers();
    ~MenuState_checkers();
    void stateEnter();
    void stateEvent();
    StateEnum stateUpdate();
    void stateRender();
    bool stateExit();
private:
    bool hover[3] = {false, false, false};
    Button_checkers*boardButtons;
    void drawMenu();
    bool loadMedia();
    bool userQuit;
};


#endif /* MenuState_h */
