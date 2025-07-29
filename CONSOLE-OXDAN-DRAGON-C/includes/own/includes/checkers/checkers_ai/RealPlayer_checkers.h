//
//  RealPlayer.h
//  SDL_Checkers
//
//  Created by Jacky Chiu on 2016-03-02.
//  Copyright © 2016 Jacky Chiu. All rights reserved.
//

#ifndef RealPlayer_h
#define RealPlayer_h

#include "Player_checkers.h"

class RealPlayer_checkers : public Player_checkers {
public:
    RealPlayer_checkers(bool, CheckersBoard_checkers*, Button_checkers*);
    ~RealPlayer_checkers();
    bool makeMove(SDL_Event *);
private:
    void selectPiece(int, int);
    bool selectedLocationIsValid(int, int, int, bool);
    void highlightValidMoves();
    bool selectingState;
};


#endif /* RealPlayer_h */
