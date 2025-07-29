#include <windows.h>
#include <iostream>
#include <conio.h>
#include "all_diclarations.h"

#pragma warning(disable : 4996).

using namespace std;

HANDLE hStdOuttgf = GetStdHandle(STD_OUTPUT_HANDLE);

void ConsoleCursorVisibleytg(bool show, short size)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOuttgf, &structCursorInfo);
	structCursorInfo.bVisible = show;
	structCursorInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOuttgf, &structCursorInfo);
}

void first_start()
{
	ConsoleCursorVisibleytg(false, 100);
	system("mode 152, 29"); // set size of console (+)
	SetWindow(600, 600); // set buffer size of console (+)

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	#define ESC 27
	#define UP 72
	#define DOWN 80

	system("cls");
	string Menu[] = { "REGISTRATION                       ", "LOGIN                         ", "SKIP                             ", "INSTRUCTIONS                             ", "EXIT                             "};

	int active_menu = 0;

	char chch;
	while (true)
	{
		int xx = 50, yy = 12;
		gotoxy(xx, yy);

		for (int i = 0; i < size(Menu); i++)
		{
			if (i == active_menu) SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
			else SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN);

			gotoxy(xx, yy++);
			cout << Menu[i] << endl;
		}

		chch = getch();

		if (chch == ESC)
		{
			system("cls");
			exit(0);
		}
		if (chch == UP)
		{
			system("cls");
			if (active_menu > 0) --active_menu;
		}

		if (chch == DOWN)
		{
			system("cls");
			if (active_menu < size(Menu) - 1) ++active_menu;
		}
		if (chch == 13) // enter
		{
			if (active_menu == 0) // 1
			{
				registration();
			}

			if (active_menu == 1) // 2
			{
				login();
			}

			if (active_menu == 2) // 3
			{
				system("cls");
				printf("\033[0;33mOxdan"); // intro cmd (+)
				printf("\033[0;31m Dragon");
				printf("\033[0;37m [ Version: 1.2025 [ENGLISH] (C/C++) [WINDOWS] ] \n");
				printf("(p) Oxdan Praduction. \n");
				start_start(true);
			}

			if (active_menu == 3) // 4
			{
				instructions();
			}

			

			if (active_menu == 4) // 5
			{
				exit(0);
			}

		}

		else if (chch == 49) // 1
		{
			registration();
		}

		else if (chch == 50) // 2
		{
			login();
		}

		else if (chch == 51) // 3
		{
			system("cls");
			printf("\033[0;33mOxdan"); // intro cmd (+)
			printf("\033[0;31m Dragon");
			printf("\033[0;37m [ Version: 1.2025 [ENGLISH] (C/C++) [WINDOWS] ] \n");
			printf("(p) Oxdan Praduction. \n");
			start_start(true);
		}

		else if (chch == 52) // 4
		{
			instructions();
		}

		else if (chch == 53) // 5
		{
			exit(0);
		}
	}
}