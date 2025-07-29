#include<iostream>
#include<conio.h>
#include<dos.h> 
#include <windows.h>
#include <time.h>
#include "all_diclarations.h"

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70 

using namespace std;

#pragma warning(disable : 4996).

char keys[10];
int keyPos[10][2];
int score_typing_tutor = 0;

void drawBorder() {
	for (int i = 0; i < SCREEN_WIDTH; i++) {
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

void genAlphabet(int ind) {
	keys[ind] = 65 + rand() % 25;
	keyPos[ind][0] = 2 + rand() % (WIN_WIDTH - 2);
	keyPos[ind][1] = 1;
}
void drawAlphabet(int ind) {
	if (keyPos[ind][0] != 0) {
		gotoxy(keyPos[ind][0], keyPos[ind][1]);   cout << keys[ind];
	}
}
void eraseAlphabet(int ind) {
	if (keyPos[ind][0] != 0) {
		gotoxy(keyPos[ind][0], keyPos[ind][1]);   cout << " ";
	}
}
void resetAlphabet(int ind) {
	eraseAlphabet(ind);
	genAlphabet(ind);
}

void gameover_tt() {
	system("cls");
	cout << endl;
	cout << "\033[0;31m\t\t--------------------------" << endl;
	cout << "\t\t-------- Game Over -------" << endl;
	cout << "\t\t--------------------------" << endl;
	cout << "\n\033[0;33m\t\tScore: \033[0;37m" << score_typing_tutor << endl;
	cout << "\n\033[0;37m\t\tPress any key to go back to menu.\n";
	getch();
	system("mode 147, 29"); // set size of console (+)
	SetWindow(147, 29); // set buffer size of console (+)
	check_start_start();
	
}
void updateScore_tt() {
	gotoxy(WIN_WIDTH + 7, 5); cout << "\033[0;33mScore: \033[0;37m" << score_typing_tutor << endl;
}

void typing_tutor_start() {
	score_typing_tutor = 0;
	for (int i = 0; i < 10; i++) {
		keyPos[i][0] = keyPos[i][1] = 1;
	}

	system("cls");
	drawBorder();
	updateScore_tt();

	for (int i = 0; i < 10; i++)
		genAlphabet(i);

	gotoxy(WIN_WIDTH + 5, 2); cout << "Typing Tutor";
	gotoxy(WIN_WIDTH + 6, 4); cout << "----------";
	gotoxy(WIN_WIDTH + 6, 6); cout << "----------";

	gotoxy(18, 5); cout << "Press any key to start";
	getch();
	gotoxy(18, 5); cout << "                      ";
	bool starting_play = true;
	while (starting_play) {
		if (kbhit()) {
			char ch = getch();
			for (int i = 0; i < 10; i++) {
				if (ch == keys[i] || ch - 32 == keys[i]) {
					resetAlphabet(i);
					score_typing_tutor++;
					updateScore_tt();
				}
			}
			if (ch == 27) {
				starting_play = false;
				system("cls");
				system("mode 147, 29"); // set size of console (+)
				SetWindow(147, 29); // set buffer size of console (+)
				check_start_start();
			}
		}

		for (int i = 0; i < 10; i++)
			drawAlphabet(i);

		Sleep(300);

		for (int i = 0; i < 10; i++) {
			eraseAlphabet(i);
			keyPos[i][1] += 1;
			if (keyPos[i][1] > SCREEN_HEIGHT) {
				gameover_tt();
				return;
			}
		}
	}
}
