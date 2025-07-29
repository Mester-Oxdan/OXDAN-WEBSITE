#include <windows.h>
#include <iostream>
#include <conio.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include "all_diclarations.h"
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#pragma warning(disable : 4996).

using namespace std;

int board[3][3];	// board for gameplay
int turn;			// current move
int result;			// Result of the game
bool over;			// Is the game Over?

/*
	Sets the board for Tic Tac Toe
*/
void Intialize()
{
	turn = 1;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			board[i][j] = 0;
	}
}
/*
	Called when any key from keyboard is pressed
*/

/*
	Called when Mouse is clicked
*/
void OnMouseClick(int button, int state, int x, int y)
{
	if (over == false && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (turn == 1)
		{
			if (board[(y - 50) / 100][x / 100] == 0)
			{
				board[(y - 50) / 100][x / 100] = 1;
				turn = 2;
			}
		}
		else if (turn == 2)
		{
			if (board[(y - 50) / 100][x / 100] == 0)
			{
				board[(y - 50) / 100][x / 100] = 2;
				turn = 1;
			}
		}
	}
}

/*
	Utility function to draw string
*/
void DrawString(void* font, const char s[], float x, float y)
{
	unsigned int i;
	glRasterPos2f(x, y);
	for (i = 0; i < strlen(s); i++)
	{
		glutBitmapCharacter(font, s[i]);
	}
}

/*
	Function to draw up the horizontal and vertical lines
*/
void DrawLines()
{
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);

	glVertex2f(100, 50);
	glVertex2f(100, 340);
	glVertex2f(200, 340);
	glVertex2f(200, 50);

	glVertex2f(0, 150);
	glVertex2f(300, 150);
	glVertex2f(0, 250);
	glVertex2f(300, 250);

	glEnd();
}

/*
	Utility function to draw the circle
*/
void DrawCircle(float cx, float cy, float r, int num_segments)
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < num_segments; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle 
		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 
		glVertex2f(x + cx, y + cy);//output vertex 
	}
	glEnd();
}

/*
	Function to draw the cross and circle of Tic Tac Toe
*/
void DrawXO()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == 1)
			{
				glBegin(GL_LINES);
				glVertex2f(50 + j * 100 - 25, 100 + i * 100 - 25);
				glVertex2f(50 + j * 100 + 25, 100 + i * 100 + 25);
				glVertex2f(50 + j * 100 - 25, 100 + i * 100 + 25);
				glVertex2f(50 + j * 100 + 25, 100 + i * 100 - 25);
				glEnd();
			}
			else if (board[i][j] == 2)
			{

				DrawCircle(50 + j * 100, 100 + i * 100, 25, 15);
			}
		}
	}
}

/*
	Function to check if there is any winner
*/
bool CheckWinner()
{
	int i, j;
	// horizontal check
	for (i = 0; i < 3; i++)
	{
		for (j = 1; j < 3; j++)
		{
			if (board[i][0] != 0 && board[i][0] == board[i][j])
			{
				if (j == 2)
				{
					return true;
				}
			}
			else
				break;
		}
	}
	// vertical check
	for (i = 0; i < 3; i++)
	{
		for (j = 1; j < 3; j++)
		{
			if (board[0][i] != 0 && board[0][i] == board[j][i])
			{
				if (j == 2)
					return true;
			}
			else
				break;
		}
	}
	// Diagonal check
	if ((board[0][0] != 0 && board[0][0] == board[1][1] && board[0][0] == board[2][2])
		|| (board[2][0] != 0 && board[2][0] == board[1][1] && board[2][0] == board[0][2]))
		return true;
	return false;
}

/*
	function to check if there is draw
*/
bool CheckIfDraw()
{
	int i, j;
	bool draw;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (board[i][j] == 0)
				return false;
		}
	}
	return true;
}

/*
	Function to display up everything
*/
void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	glColor3f(0, 0, 0);
	if (turn == 1)
		DrawString(GLUT_BITMAP_HELVETICA_18, "Player 1 turn", 100, 30);
	else
		DrawString(GLUT_BITMAP_HELVETICA_18, "Player 2 turn", 100, 30);

	DrawLines();
	DrawXO();

	if (CheckWinner() == true)
	{
		if (turn == 1)
		{
			over = true;
			result = 2;
		}
		else
		{
			over = true;
			result = 1;
		}
	}
	else if (CheckIfDraw() == true)
	{
		over = true;
		result = 0;
	}
	if (over == true)
	{
		glColor3f(255, 0, 0);
		DrawString(GLUT_BITMAP_HELVETICA_18, "!Game Over!", 99, 160);

		if (result == 0)
		{
			glColor3f(1, 0.5, 0);
			DrawString(GLUT_BITMAP_HELVETICA_18, "!Game draw!", 99, 185);
			glColor3f(0, 0, 0);
		}
		if (result == 1)
		{
			glColor3f(1, 0.5, 0);
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player 1: !win!", 93, 185);
			glColor3f(0, 0, 0);
		}
		if (result == 2)
		{
			glColor3f(1, 0.5, 0);
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player 2: !win!", 93, 185);
			glColor3f(0, 0, 0);
		}
	}
	int cur_win_ok = glutGetWindow();
	if (cur_win_ok) glutSwapBuffers();
}

/*
	Function to reshape
*/
void Reshape(int x, int y)
{
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, x, y, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}

// Function to set the window icon
void setWindowIcon_17(const char* path) {
	HINSTANCE hInstance = GetModuleHandle(NULL);
	HICON hIcon = (HICON)LoadImageA(hInstance, path, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	if (hIcon) {
		HWND hwnd = FindWindowA(NULL, "Tic Tac Toe 2"); // Ensure this matches the title set in glutCreateWindow
		if (hwnd) {
			SendMessage(hwnd, WM_SETICON, (WPARAM)ICON_BIG, (LPARAM)hIcon);
			SendMessage(hwnd, WM_SETICON, (WPARAM)ICON_SMALL, (LPARAM)hIcon);
		}
	}
	else {
		MessageBoxA(NULL, "Failed to load icon.", "Error", MB_OK | MB_ICONERROR);
	}
}

void tic_tac_toe_2_start()
{
	// add icon

	int argc;
	char** argv = nullptr;

	Intialize();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(550, 200);
	glutInitWindowSize(300, 350);
	glutCreateWindow("Tic Tac Toe 2");
	glutReshapeFunc(Reshape);
	string text_icon = oxdan_dragon_c + "\\my_dragon_ico.ico";
	setWindowIcon_17(text_icon.c_str());
	glutDisplayFunc(Display);
	//glutKeyboardFunc(Intialize);
	glutMouseFunc(OnMouseClick);
	glutIdleFunc(Display);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutMainLoop();

	
}