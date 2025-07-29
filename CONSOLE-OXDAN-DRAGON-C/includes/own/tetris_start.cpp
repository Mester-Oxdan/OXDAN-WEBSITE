#include <windows.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <time.h>
#include "game_tetris.hpp"
//#include "stb_image.h"
#include "all_diclarations.h"

Game_tetris game;
bool isWindowClosed_9 = false;

// Initialize OpenGL settings
void init_tetris(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

// Function to draw the game board
void drawBoard(void) {
    if (isWindowClosed_9) {
        check_start_start();
    }

    glViewport(0, 0, 300, 600);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 10, 0, 20);

    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 10; x++) {
            if (game.getOccupied(x, y) ^ game.getCurrent(x, y)) {
                glColor3f(game.getRed(x, y), game.getGreen(x, y), game.getBlue(x, y));
                glRectd(x, y, x + 1, y + 1);
            }
            else {
                glColor3f(0.0, 0.0, 0.0);
                glRectd(x, y, x + 1, y + 1);
            }
        }
    }

    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    for (int i = 0; i < 20; i++) {
        glVertex2f(i, 0.0);
        glVertex2f(i, 20.0);
        glVertex2f(0.0, i);
        glVertex2f(20.0, i);
    }
    glEnd();

    int cur_win_6 = glutGetWindow();
    if (cur_win_6) glutSwapBuffers();
}

// Handle keyboard input for movement and quitting
void transform(int key, int x, int y) {
    int cur_win_5 = glutGetWindow();
    switch (key) {
    case GLUT_KEY_UP:
        game.rotate();
        if (cur_win_5) glutPostRedisplay();
        break;
    case GLUT_KEY_LEFT:
        game.translate(-1);
        if (cur_win_5) glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        game.translate(1);
        if (cur_win_5) glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:
        game.moveDown();
        if (cur_win_5) glutPostRedisplay();
        break;
    }
}

// Handle keyboard input for quitting and restarting the game
void quitRestart(unsigned char key, int x, int y) {
    if (key == 27) { // 27 is the ASCII code for the Escape key
        glutDestroyWindow(glutGetWindow());
        check_start_start();
    }
    if (key == 'r') {
        game.restart();
    }
}

// Timer function to move pieces down periodically
void timer(int id) {
    if (game.getGameOver() == true || isWindowClosed_9) {
        game.restart();
    }
    if (id == 0) { // Beginning of game
        game.spawnFruits();
    }
    else {
        game.moveDown();
    }
    int cur_win_1 = glutGetWindow();
    if (cur_win_1) glutPostRedisplay();
    glutTimerFunc(500, timer, id + 1);
}

// Function to set the window icon
void setWindowIcon(const char* path) {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    HICON hIcon = (HICON)LoadImageA(hInstance, path, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
    if (hIcon) {
        HWND hwnd = FindWindowA(NULL, "Tetris"); // Ensure this matches the title set in glutCreateWindow
        if (hwnd) {
            SendMessage(hwnd, WM_SETICON, (WPARAM)ICON_BIG, (LPARAM)hIcon);
            SendMessage(hwnd, WM_SETICON, (WPARAM)ICON_SMALL, (LPARAM)hIcon);
        }
    }
    else {
        MessageBoxA(NULL, "Failed to load icon.", "Error", MB_OK | MB_ICONERROR);
    }
}

// Main function to start the game
void tetris_start() {
    try {
        int argc = 0;
        char** argv = NULL;

        srand(time(NULL));
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        glutInitWindowPosition(500, 50);
        glutInitWindowSize(300, 600);
        glutCreateWindow("Tetris");

        // Set the window icon
        string text_icon = oxdan_dragon_c + "\\my_dragon_ico.ico";
        setWindowIcon(text_icon.c_str());

        // Initialize the game
        init_tetris();

        // Register callback functions
        glutDisplayFunc(drawBoard);
        glutSpecialFunc(transform);
        glutKeyboardFunc(quitRestart);
        glutTimerFunc(500, timer, 0);

        glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

        // Enter the GLUT main loop
        if (!isWindowClosed_9) {
            glutMainLoop();
        }

        check_start_start();
    }
    catch (...) {
        check_start_start();
    }
}
