//
//  Player.h
//  CheckersProject
//
//  Created by Benjamin Emdon on 2016-02-13.
//  Copyright © 2016 Ben Emdon. 
//

#ifndef Player_h
#define Player_h

#include "CheckersBoard_checkers.h"
#include "Piece_checkers.h"

using namespace std;

class Button_checkers;

class Player_checkers {
public:
    Player_checkers(bool,CheckersBoard_checkers*, Button_checkers*);
    ~Player_checkers();
    virtual bool makeMove(SDL_Event *);
    vector<Piece> team;
    bool turn;
    void updateTeam();
    void updateKings();
    
    // for multi turn loop
    bool killWasMade = false;
protected:
    void movePiece(vector<vector<int>> &, vector<Piece> & ,int, int, int);
    void killPiece(vector<vector<int>> &, int, int);
    void initTeam();
    bool sameTeam(int,int);
    int pieceTeamIndexByXY(int,int);
    int currentIndex;
    bool topSide;
    int ONE;
    int TEAM_NUMBER;
    int ENEMY_TEAM_NUMBER;
    CheckersBoard_checkers*Board;
    Button_checkers*boardButtons;
    
    // for multi turn loop
    int killerPeiceIndex;
};


#endif /* Player_h */
