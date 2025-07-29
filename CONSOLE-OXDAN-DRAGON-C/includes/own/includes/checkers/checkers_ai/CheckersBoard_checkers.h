//
//  CheckersBoard.h
//  Checkers
//
//  Created by Jacky Chiu on 2016-02-13.
//  Copyright © 2016 Jacky Chiu. 
//

#ifndef CheckersBoard_h
#define CheckersBoard_h

#include <vector>
#include <iostream>
#include "Application_checkers.h"
#include "Button_checkers.h"

struct pointXY {
    int x;
    int y;
};


class CheckersBoard_checkers {
    friend ostream & operator << (ostream &, CheckersBoard_checkers&);
public:
    CheckersBoard_checkers();
    ~CheckersBoard_checkers();
    void drawBoard();
    void drawHighlights();
    void turnHighLightOn(int,int);
    void turnHighLightOff();
    vector<vector<int>> virtualBoard; // Virtual board inexed by [x][y]
    void drawBoardPeices(int, int, Button_checkers*);
    bool emptyBoard();
    vector<pointXY> validLocations;
private:
    bool highLight;
    pointXY highLightSelected;
    
};

//extern CheckersBoard Board;
#endif /* CheckersBoard_h */
