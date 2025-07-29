#include <windows.h>
#include <conio.h>
#include <iostream>
#include "all_diclarations.h"

#pragma warning(disable : 4996).

using namespace std;

char l[] = "บบบบบ";
int i;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void printBorder() {
	for (i = 2; i <= 79; i++) {
		gotoxy(i, 1);
		cout << '-';
		gotoxy(i, 25);
		cout << '-';
	}
	for (i = 1; i <= 25; i++) {
		gotoxy(2, i);
		cout << '|';
		gotoxy(79, i);
		cout << '|';
	}
}

void setplayers() {
	system("cls");
	printBorder();
	gotoxy(4, 3);
	cout << "\033[0;33mSCORE:\033[0;37m 0";
	gotoxy(50, 3);
	cout << "\033[0;31mPress 'Esc' for exit\033[0;37m";
	for (i = 3; i <= 78; i++) {
		gotoxy(i, 4);
		cout << '-';
	}
	for (i = 0; i <= strlen(l); i++) {
		gotoxy(5, 5 + i);
		cout << l[i];
	}
	for (i = 0; i <= strlen(l); i++) {
		gotoxy(76, 5 + i);
		cout << l[i];
	}
}

void gameplay() {
	setplayers();
	int sc = 0, pp = 0, st = 1;
	int c = 5, k = 5, x = 73, y = 6 + rand() % 15;
	int d = rand() % 2, px, py;
	int op = 1, go = 1;
	int rld = 0, rlu = 0, lru = 0, lrd = 0;

	while (1) {
		if (go == 1) {
			while (!kbhit() && op) {
				px = x;
				py = y;
				gotoxy(x, y);
				cout << "\033[0;31mO\033[0;37m";
				Sleep(50);
				gotoxy(x, y);
				cout << " ";

				if (st == 1) {
					st = 0;
					if (d == 0) {
						x--;
						y++;
					}
					else {
						x--;
						y--;
					}
				}

				if (rld) {
					x--;
					y++;
				}
				if (rlu) {
					x--;
					y--;
				}
				if (lru) {
					x++;
					y--;
				}
				if (lrd) {
					x++;
					y++;
				}

				if (x < px && y > py) rld = 1;
				if (x < px && y < py) rlu = 1;
				if (y == 5 && rlu) {
					rld = 1;
					rlu = 0;
				}
				if (y == 24 && rld) {
					rlu = 1;
					rld = 0;
				}
				if (x == 6 && rlu) {
					lru = 1;
					rlu = 0;
				}
				if (x == 6 && rld) {
					lrd = 1;
					rld = 0;
				}
				if (y == 5 && lru) {
					lrd = 1;
					lru = 0;
				}
				if (y == 24 && lrd) {
					lru = 1;
					lrd = 0;
				}
				if (x == 75 && lrd) {
					rld = 1;
					lrd = 0;
				}
				if (x == 75 && lru) {
					rlu = 1;
					lru = 0;
				}

				if (x == 75 || x == 6) {
					Sleep(50);
				}
				if (y == 5 || y == 24) {
					Sleep(50);
				}

				if (lru || lrd) {
					if (y >= 6 && y <= 22) {
						if (y > k + strlen(l) - 3) {
							gotoxy(76, k + strlen(l));
							cout << "บ";
							gotoxy(76, k);
							if (k != 4) cout << ' ';
							k++;
						}
						if (y < k + strlen(l) - 3) {
							gotoxy(76, k);
							cout << "บ";
							gotoxy(76, k + strlen(l));
							if (k + strlen(l) != 25) cout << ' ';
							k--;
						}
					}
				}

				if (x == 6 && (y < c || y > c + strlen(l) - 1)) {
					gotoxy(x, y);
					cout << "\033[0;31m!YOU LOSE!\033[0;37m Press 'r' or 'ENTER' to play again!";
					op = 0;
					break;
				}

				if (x == 6 && op == 1) {
					gotoxy(4, 3);
					cout << "\033[0;33mSCORE:\033[0;37m " << ++sc;
				}

			}
		}

		char ch = getch();

		if (ch == 'p' && op == 1) {
			pp = 1;
			go = 0;
			gotoxy(22, 12);
			cout << "\033[0;33m!GAME PAUSED!\033[0;37m PRESS ENTER to continue !";
		}
		if (ch == 13 && pp && op == 1) {
			pp = 0;
			go = 1;
			gotoxy(22, 12);
			cout << "                                       ";
		}
		if ((ch == 'r' || ch == 'R' || ch == 13) && op == 0) {
			op = 1;
			gameplay();
			break;
		}
		if ((ch == 's' || ch == 'S' || ch == 80) && c <= 19 && op) {
			gotoxy(5, c + strlen(l));
			cout << "บ";
			gotoxy(5, c);
			cout << ' ';
			c++;
		}
		if ((ch == 'w' || ch == 'W' || ch == 72) && c >= 6 && op) {
			gotoxy(5, c - 1);
			cout << "บ";
			gotoxy(5, c + 4);
			cout << ' ';
			c--;
		}
		if (ch == 27) {
			break;
		}
	}
}

void setcursor(bool visible, DWORD size) // set bool visible = 0 - invisible, bool visible = 1 - visible
{
	if (size == 0) {
		size = 20; // default cursor size Changing to numbers from 1 to 20, decreases cursor width
	}
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console, &lpCursor);
}

void ping_pong_ai_start()
{
	system("mode 84, 28"); // set size of console (+)
	SetWindow(600, 600); // set buffer size of console (+)
	setcursor(0, 0);
	srand((unsigned)time(NULL));
	system("cls");
	//	printBorder();
	gameplay();

	if (GetKeyState(VK_ESCAPE) < 0)
	{
		system("mode 141, 29"); // set size of console (+)
		SetWindow(600, 600); // set buffer size of console (+)
		check_start_start();
	}
}