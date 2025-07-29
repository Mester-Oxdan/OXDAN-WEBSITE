//
//  GameState.h
//  SDL_Checkers
//
//  Created by Jacky Chiu on 2016-02-25.
//  Copyright © 2016 Jacky Chiu.
//

#ifndef GameState_h
#define GameState_h

#ifdef _WIN32
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#endif

#ifdef __linux
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif

#include "ApplicationState_checkers.h"
#include "Application_checkers.h"

enum SpriteList{
    EMPTY_PIECE,
    RED_PIECE,
    BLACK_PIECE,
    RED_KING,
    BLACK_KING,
    TOTAL_PIECES
};

class ApplicationStateManager_checkers;
class Button_checkers;
class CheckersBoard_checkers;
class Player_checkers;
class AI_checkers;
class Texture_checkers;

class GameState_checkers : public ApplicationState{
public:
    GameState_checkers();
    ~GameState_checkers();
    void stateEnter();
    void stateEvent();
    StateEnum stateUpdate();
    void stateRender();
    bool stateExit();
private:
    bool loadMedia();
    bool gameOver();
    CheckersBoard_checkers *Board;
    Button_checkers *boardButtons;
    Player_checkers *Player1;
    Player_checkers *Player2;
    bool userQuit;
};


#endif /* GameState_h */
