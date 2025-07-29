#include <windows.h>
#include <conio.h>
#include <iostream>
#include "all_diclarations.h"

#pragma warning(disable : 4996).

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define MENU_WIDTH 20
#define GAP_SIZE 7

using namespace std;

int pipePos[3];
int gapPos[3];
int pipeFlag[3];
char bird[2][6] = { 'o','>' };
int birdPos = 6;
int score567 = 0;

void drawBorderflp() {

	for (int i = 0; i < SCREEN_WIDTH; i++) {
		gotoxy(i, 0); cout << "±";
		gotoxy(i, SCREEN_HEIGHT); cout << "±";
	}

	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		gotoxy(0, i); cout << "±";
		gotoxy(SCREEN_WIDTH, i); cout << "±";
	}
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		gotoxy(WIN_WIDTH, i); cout << "±";
	}
}
void genPipe(int ind) {
	gapPos[ind] = 3 + rand() % 14;
}
void drawPipe(int ind) {
	if (pipeFlag[ind] == true) {
		for (int i = 0; i < gapPos[ind]; i++) {
			gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "\033[0;32m***\033[0;37m";
		}
		for (int i = gapPos[ind] + GAP_SIZE; i < SCREEN_HEIGHT - 1; i++) {
			gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "\033[0;32m***\033[0;37m";
		}
	}
}
void erasePipe(int ind) {
	if (pipeFlag[ind] == true) {
		for (int i = 0; i < gapPos[ind]; i++) {
			gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "   ";
		}
		for (int i = gapPos[ind] + GAP_SIZE; i < SCREEN_HEIGHT - 1; i++) {
			gotoxy(WIN_WIDTH - pipePos[ind], i + 1); cout << "   ";
		}
	}
}

void drawBird() {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 6; j++) {
			gotoxy(j + 2, i + birdPos); cout << "\033[0;33m" << bird[i][j] << "\033[0;37m";
		}
	}
}
void eraseBird() {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 6; j++) {
			gotoxy(j + 2, i + birdPos); cout << " ";
		}
	}
}

int collision() {
	if (pipePos[0] >= 61) {
		if (birdPos<gapPos[0] || birdPos >gapPos[0] + GAP_SIZE) {
			//			cout<< " HIT ";
			//			getch();
			return 1;
		}
	}
	return 0;
}

void gameover() {
	system("cls");
	cout << endl;
	cout << "\t\t\033[0;31m--------------------------" << endl;
	cout << "\t\t-------- Game Over -------" << endl;
	cout << "\t\t--------------------------\033[0;37m" << endl << endl;

	cout << "\t\t         \033[0;33mScore: \033[0;37m" << score567 << endl;

	cout << "\t\tPress any key to go back to menu.\n";
	getch();
	
}
void updateScore() {
	gotoxy(WIN_WIDTH + 5, 5); cout << "- \033[0;33mScore: \033[0;37m" << score567 << endl;
}

void flappybird_start()
{
	birdPos = 6;
	score567 = 0;
	pipeFlag[0] = 1;
	pipeFlag[1] = 0;
	pipePos[0] = pipePos[1] = 4;

	system("cls");

	if (GetKeyState(VK_ESCAPE) < 0)
	{
		printf("\n");
		check_start_start();
	}

	drawBorderflp();
	genPipe(0);
	updateScore();

	gotoxy(WIN_WIDTH + 5, 2); cout << "\033[0;32mFLAPPY \033[0;34mBIRD\033[0;37m";
	gotoxy(WIN_WIDTH + 5, 4); cout << "------------";
	gotoxy(WIN_WIDTH + 5, 6); cout << "------------";
	gotoxy(WIN_WIDTH + 7, 12); cout << "Control ";
	gotoxy(WIN_WIDTH + 6, 13); cout << "--------- ";
	gotoxy(WIN_WIDTH + 2, 14); cout << " Spacebar = jump";

	gotoxy(10, 5); cout << "Press any key to start";
	getch();
	gotoxy(10, 5); cout << "                      ";

	while (1) {

		if (kbhit()) {
			char ch = getch();
			if (ch == 32) {
				if (birdPos > 3)
					birdPos -= 3;
			}
			if (ch == 27) {
				break;
			}
		}

		drawBird();
		drawPipe(0);
		drawPipe(1);
		if (collision() == 1) {
			gameover();
			check_start_start();
		}
		Sleep(100);
		eraseBird();
		erasePipe(0);
		erasePipe(1);
		birdPos += 1;

		if (birdPos > SCREEN_HEIGHT - 2) {
			gameover();
			printf("\n");
			check_start_start();
		}

		if (pipeFlag[0] == 1)
			pipePos[0] += 2;

		if (pipeFlag[1] == 1)
			pipePos[1] += 2;

		if (pipePos[0] >= 40 && pipePos[0] < 42) {
			pipeFlag[1] = 1;
			pipePos[1] = 4;
			genPipe(1);
		}
		if (pipePos[0] > 68) {
			score567++;
			updateScore();
			pipeFlag[1] = 0;
			pipePos[0] = pipePos[1];
			gapPos[0] = gapPos[1];
		}

	}
}