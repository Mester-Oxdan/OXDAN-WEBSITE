#include "game_tetris.hpp"
#include <time.h>
#include <stdlib.h>
#include <ostream>

Game_tetris::Game_tetris() {
    board.resize(10);
    for (int k = 0; k < 10; k++) {
        board[k].resize(20);
    }
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 10; x++) {
            board[x][y].isOccupied = false;
            board[x][y].isCurrent = false;
        }
    }
}
Game_tetris::~Game_tetris() {
    board.clear();
}

void Game_tetris::restart() {
    board.resize(10);
    for (int k = 0; k < 10; k++) {
        board[k].resize(20);
    }
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 10; x++) {
            board[x][y].isOccupied = false;
            board[x][y].isCurrent = false;
        }
    }
    game_over = false;
    spawnFruits();
}
bool Game_tetris::getGameOver() {
    return game_over;
}
bool Game_tetris::getCurrent(int x, int y) {
    return board[x][y].isCurrent;
}
bool Game_tetris::getOccupied(int x, int y) {
    return board[x][y].isOccupied;
}
float Game_tetris::getRed(int x, int y) {
    return board[x][y].red;
}
float Game_tetris::getGreen(int x, int y) {
    return board[x][y].green;
}
float Game_tetris::getBlue(int x, int y) {
    return board[x][y].blue;
}
float Game_tetris::getRGB(Colortetris color, int RGB) {
    switch (color) {
    case purple:
        return colors[0][RGB];
    case red:
        return colors[1][RGB];
    case green:
        return colors[2][RGB];
    case yellow:
        return colors[3][RGB];
    case orange:
        return colors[4][RGB];
    }
    return -1;
}
void Game_tetris::setCurrent(int x, int y) {
    clearPreviousFrame();
    curr_x = x;
    curr_y = y;
    updateActiveFruits();

}

void Game_tetris::spawnFruits() {
    int shape = rand() % 7;
    int rotation = rand() % 4;
    Colortetris color;
    int position = (rand() % 5) + 2;
    for (int i = 0; i < 4; i++) {
        color = static_cast<Colortetris>(rand() % orange);
        curr_colors[i] = color;
    }
    curr_shape = shape;
    curr_rotation = rotation;
    if (checkCollision(position, 17, rotation)) {
        game_over = true;
    }
    else {
        curr_shape = shape;
        curr_rotation = rotation;
        curr_x = position;
        curr_y = 17;
        updateActiveFruits();
    }



}
void Game_tetris::rotate() {
    int rotation;
    if (curr_rotation > 0) {
        rotation = curr_rotation - 1;
    }
    else {
        rotation = 3;
    }
    if (!(checkCollision(curr_x, curr_y, rotation))) {
        clearPreviousFrame();
        curr_rotation = rotation;
        updateActiveFruits();
    }
}
void Game_tetris::translate(int direction) {
    int new_x = curr_x + direction;
    if (!(checkCollision(new_x, curr_y, curr_rotation))) {
        clearPreviousFrame();
        curr_x = new_x;
        updateActiveFruits();
    }

}
void Game_tetris::moveDown() {
    if (!(checkCollision(curr_x, curr_y - 1, curr_rotation))) {
        clearPreviousFrame();
        curr_y -= 1;
        updateActiveFruits();
    }
    else {
        freezeCurrent();
        clearLines();
        spawnFruits();
    }
}
void Game_tetris::freezeCurrent() {
    board[curr_x][curr_y].isOccupied = true;
    board[curr_x][curr_y].isCurrent = false;
    board[curr_x][curr_y].red = getRGB(curr_colors[0], 0);
    board[curr_x][curr_y].green = getRGB(curr_colors[0], 1);
    board[curr_x][curr_y].blue = getRGB(curr_colors[0], 2);
    int k = 1;
    for (int i = 1; i < 6; i += 2) {
        board[curr_x + shapes[curr_shape][curr_rotation][i - 1]][curr_y + shapes[curr_shape][curr_rotation][i]].isOccupied = true;
        board[curr_x + shapes[curr_shape][curr_rotation][i - 1]][curr_y + shapes[curr_shape][curr_rotation][i]].isCurrent = false;
        board[curr_x + shapes[curr_shape][curr_rotation][i - 1]][curr_y + shapes[curr_shape][curr_rotation][i]].red = getRGB(curr_colors[k], 0);
        board[curr_x + shapes[curr_shape][curr_rotation][i - 1]][curr_y + shapes[curr_shape][curr_rotation][i]].green = getRGB(curr_colors[k], 1);
        board[curr_x + shapes[curr_shape][curr_rotation][i - 1]][curr_y + shapes[curr_shape][curr_rotation][i]].blue = getRGB(curr_colors[k], 2);
        k += 1;
    }
}
void Game_tetris::clearLines() {
    checkRow();
    //checkFruits();
}

void Game_tetris::checkRow() {
    bool full;
    for (int y = 0; y < 20; y++) {
        full = true;
        for (int x = 0; x < 10; x++) {
            if (!(board[x][y].isOccupied)) {
                full = false;
                break;
            }
        }
        if (full) {
            deleteRow(y);
            y--;
        }
    }
}
void Game_tetris::deleteRow(int y) {
    for (int k = y; k < 19; k++) {
        for (int x = 0; x < 10; x++) {
            board[x][k].isOccupied = board[x][k + 1].isOccupied;
            board[x][k].isCurrent = board[x][k + 1].isCurrent;
            board[x][k].red = board[x][k + 1].red;
            board[x][k].green = board[x][k + 1].green;
            board[x][k].blue = board[x][k + 1].blue;
        }
    }
    for (int x = 0; x < 10; x++) {
        board[x][19].isOccupied = false;
        board[x][19].isCurrent = false;
    }
}
void Game_tetris::clearPreviousFrame() {
    if (curr_x < 10 && curr_x > -1 && curr_y < 20 && curr_y > -1) {
        //board[curr_x][curr_y].isOccupied = false;
        board[curr_x][curr_y].isCurrent = false;
    }
    for (int i = 1; i < 6; i += 2) {
        if (curr_x + shapes[curr_shape][curr_rotation][i - 1] < 10 &&
            curr_x + shapes[curr_shape][curr_rotation][i - 1] > -1 &&
            curr_y + shapes[curr_shape][curr_rotation][i] < 20 &&
            curr_y + shapes[curr_shape][curr_rotation][i] > -1) {
            //board[curr_x+shapes[curr_shape][curr_rotation][i-1]][curr_y+shapes[curr_shape][curr_rotation][i]].isOccupied = false;
            board[curr_x + shapes[curr_shape][curr_rotation][i - 1]][curr_y + shapes[curr_shape][curr_rotation][i]].isCurrent = false;
        }
    }
}
bool Game_tetris::checkCollision(int x, int y, int rotation) {
    int xpos[4] = { x,
    x + shapes[curr_shape][rotation][0],
    x + shapes[curr_shape][rotation][2],
    x + shapes[curr_shape][rotation][4]
    };
    int ypos[4] = { y,
        y + shapes[curr_shape][rotation][1],
        y + shapes[curr_shape][rotation][3],
        y + shapes[curr_shape][rotation][5]
    };
    for (int i = 0; i < 4; i++) {
        if (xpos[i] > 9 || xpos[i] < 0 || ypos[i] > 19 || ypos[i] < 0) {
            return true;
        }
        if (board[xpos[i]][ypos[i]].isOccupied) {
            return true;
        }
    }
    return false;

}
void Game_tetris::updateActiveFruits() {
    //board[curr_x][curr_y].isOccupied = true;
    if (curr_x < 10 && curr_x > -1 && curr_y < 20 && curr_y > -1) {
        board[curr_x][curr_y].isCurrent = true;
        if (!board[curr_x][curr_y].isOccupied) {
            board[curr_x][curr_y].red = getRGB(curr_colors[0], 0);
            board[curr_x][curr_y].green = getRGB(curr_colors[0], 1);
            board[curr_x][curr_y].blue = getRGB(curr_colors[0], 2);
        }
    }
    int k = 1;
    for (int i = 1; i < 6; i += 2) {
        if (curr_x + shapes[curr_shape][curr_rotation][i - 1] < 10 &&
            curr_x + shapes[curr_shape][curr_rotation][i - 1] > -1 &&
            curr_y + shapes[curr_shape][curr_rotation][i] < 20 &&
            curr_y + shapes[curr_shape][curr_rotation][i] > -1) {
            //board[curr_x+shapes[curr_shape][curr_rotation][i-1]][curr_y+shapes[curr_shape][curr_rotation][i]].isOccupied = true;
            board[curr_x + shapes[curr_shape][curr_rotation][i - 1]][curr_y + shapes[curr_shape][curr_rotation][i]].isCurrent = true;
            if (!board[curr_x + shapes[curr_shape][curr_rotation][i - 1]][curr_y + shapes[curr_shape][curr_rotation][i]].isOccupied) {
                board[curr_x + shapes[curr_shape][curr_rotation][i - 1]][curr_y + shapes[curr_shape][curr_rotation][i]].red = getRGB(curr_colors[k], 0);
                board[curr_x + shapes[curr_shape][curr_rotation][i - 1]][curr_y + shapes[curr_shape][curr_rotation][i]].green = getRGB(curr_colors[k], 1);
                board[curr_x + shapes[curr_shape][curr_rotation][i - 1]][curr_y + shapes[curr_shape][curr_rotation][i]].blue = getRGB(curr_colors[k], 2);
            }
        }
        k += 1;
    }
}

//deletes the consecutive fruit and moves the fruit above down
void Game_tetris::deleteFruit(int x1, int y1, int x2, int y2, int x3, int y3) {
    if (x1 == x2) {
        for (int k = y1; k > 3; k--) {
            shiftColumn(x1, k, 3);
        }
    }
    else {
        for (int k = y1; k > 0; k--) {
            shiftColumn(x1, k, 1);
        }
        for (int k = y2; k > 0; k--) {
            shiftColumn(x2, k, 1);
        }
        for (int k = y3; k > 0; k--) {
            shiftColumn(x3, k, 1);
        }

    }
}
//move tiles down above the selected tile
void Game_tetris::shiftColumn(int x, int k, int diff) {
    board[x][k].isOccupied = board[x][k - diff].isOccupied;
    board[x][k].isCurrent = board[x][k - diff].isCurrent;
    board[x][k].red = board[x][k - diff].red;
    board[x][k].green = board[x][k - diff].green;
    board[x][k].blue = board[x][k - diff].blue;
}

void Game_tetris::dropFruit() {
    if (!(checkCollision(curr_x, curr_y, curr_rotation))) {
        freezeCurrent();
        spawnFruits();
    }
    else {
        game_over = true;
    }
}