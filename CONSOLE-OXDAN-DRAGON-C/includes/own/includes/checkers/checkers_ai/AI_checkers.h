#ifndef AI_H
#define AI_H

#include "Player_checkers.h"
#include "CheckersBoard_checkers.h"

class AI_checkers : public Player_checkers
{
public:
    AI_checkers(bool, CheckersBoard_checkers*, Button_checkers*);
    ~AI_checkers();
    bool makeMove(SDL_Event *);
private:
    // New AI Stuff
    int findMax(int,int);
    int findMin(int,int);

    int maxValue(vector<vector<int>> tempBoard, vector<Piece> teamCopy, vector<Piece> enemyTeamCopy, int depth, Directions direction);
    int minValue(vector<vector<int>> tempBoard, vector<Piece> teamCopy, vector<Piece> enemyTeamCopy, int depth, Directions direction);

    int minMove(vector<vector<int>> tempBoard, vector<Piece> teamCopy, vector<Piece> enemyTeamCopy, int depth);
    int maxMove(vector<vector<int>> tempBoard, vector<Piece> teamCopy, vector<Piece> enemyTeamCopy, int depth);

    bool checkNode(vector<vector<int>> tempBoard, vector<Piece> teamCopy, vector<Piece> enemyTeamCopy, Directions direction, bool enemy);
    int valueCalculator(vector<Piece> teamCopy, vector<Piece> enemyTeamCopy);

    void updateTeam(vector<vector<int>> &tempBoard, vector<Piece> &teamCopy, bool enemy);

    void updateKings(vector<vector<int>> &tempBoard, vector<Piece> &teamCopy, bool enemy);

    // Old AI stuff
    void getEnemyTeam();
    bool changeWithDirection(int&,int&,Directions, bool);
    bool killCheckArea(vector<vector<int>> tempBoard, int,int,Directions, bool);
    int bestPiece(vector<Piece>);
    int enemyBestPiece(vector<Piece>);

    const int OUT_OF_BOUND = -999;
    const int WIN_VALUE = 999;
    // Temp max depth value:
    const int MAX_DEPTH = 4;

    // Used for finding min values
    vector<Piece> enemyTeam;
    int enemyCurrentIndex;
};

#endif // AI_H
