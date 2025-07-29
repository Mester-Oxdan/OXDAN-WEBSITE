//
//  CheckersBoard.cpp
//  Checkers
//
//  Created by Jacky Chiu on 2016-02-13.
//  Copyright © 2016 Jacky Chiu. 
//

#include "CheckersBoard_checkers.h"
#include "GameState_checkers.h"
#include "Texture_checkers.h"
#include <boost/concept_check.hpp>

CheckersBoard_checkers::CheckersBoard_checkers(){
    for (int y = 0; y < 8; y++)
    {
        vector<int> rowVector;
        for (int x = 0; x < 8; x++)
        {
            rowVector.push_back(0);
        }
        virtualBoard.push_back(rowVector);
    }
    highLight = false;
    highLightSelected.x = NULL;
    highLightSelected.y = NULL;
}

CheckersBoard_checkers::~CheckersBoard_checkers(){
    virtualBoard.clear();
}

ostream & operator << (ostream & output, CheckersBoard_checkers& boardPassed) {
    //output << "========" << endl;
    for (int y=0; y<8; y++) {
        for (int x=0; x<8; x++) {
            
                output << "";
                
        }
        
    }
    return output;
}

void CheckersBoard_checkers::turnHighLightOn(int x,int y){
    highLight = true;
    highLightSelected.x = x * 80;
    highLightSelected.y = y * 80;
}

void CheckersBoard_checkers::turnHighLightOff(){
    highLight = false;
    validLocations.clear();
}

void CheckersBoard_checkers::drawBoard(){
    
    bool indent = false;
    int xStart;
    // Dark wood colour //
    SDL_SetRenderDrawColor( gRenderer, 0x55, 0x27, 0x00, 0xFF );
    
    for(int y=0;y<SCREEN_HEIGHT;y+=BUTTON_HEIGHT){
        if (indent) {
            xStart = BUTTON_WIDTH;
            indent = false;
        }
        else{
            xStart = 0;
            indent = true;
        }
        for(int x=xStart;x<SCREEN_WIDTH;x+=2*BUTTON_WIDTH){
            SDL_Rect redRect = {x, y, BUTTON_WIDTH, BUTTON_HEIGHT};
            SDL_RenderFillRect( gRenderer, &redRect);
        }
    }
    drawHighlights();
    
}

void CheckersBoard_checkers::drawHighlights() {
    if (highLight) {
        // Set to white //
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        // Create the outline rect //
        SDL_Rect outLine = {highLightSelected.x, highLightSelected.y, BUTTON_WIDTH, BUTTON_HEIGHT};
        // Call to render //
        SDL_RenderDrawRect(gRenderer, &outLine);
        
        // Set to white //
        SDL_SetRenderDrawColor( gRenderer, 0x55, 0xFF, 0x55, 0xFF );
        
        for (int indexOfValidMoves = 0; indexOfValidMoves < validLocations.size(); indexOfValidMoves++) {
            SDL_Rect outLineValid = {validLocations[indexOfValidMoves].x * 80, validLocations[indexOfValidMoves].y * 80, BUTTON_WIDTH, BUTTON_HEIGHT};
            // Call to render //
            SDL_RenderDrawRect(gRenderer, &outLineValid);
        }
    }
}

void CheckersBoard_checkers::drawBoardPeices(int x, int y, Button_checkers*boardButton){
    switch (virtualBoard[x][y]) {
            
        case RED_PIECE:
            currentSprite = RED_PIECE;
            boardButton->render(currentSprite-1);
            break;
            
        case BLACK_PIECE:
            currentSprite = BLACK_PIECE;
            boardButton->render(currentSprite-1);
            break;
            
        case RED_KING:
            currentSprite = RED_KING;
            boardButton->render(currentSprite-1);
            break;
            
        case BLACK_KING:
            currentSprite = BLACK_KING;
            boardButton->render(currentSprite-1);
            break;

        default:
            break;
    }

}
   