#include <windows.h>
#include <stdio.h>
#include <iostream>
#include "all_diclarations.h"

using namespace std;

void displayTime(int hours, int minutes, int seconds)
{

	system("cls");

	// for windows
	// system("cls");
	gotoxy(60, 11);
	printf("\033[0;31mPress 'Esc' for exit \033[0;37m\n");

	gotoxy(67, 12); cout << hours << ":"
		<< minutes << ":"
		<< seconds << endl;
}

void stopwatch_start()
{
	int hour = 0;
	int min = 0;
	int sec = 0;

	displayTime(hour, min, sec);

	while (true) {
		Sleep(1000);

		sec++;

		if (sec > 59) {
			min++;
			sec = 0;
		}

		if (min > 59) {
			hour++;
			sec = 0;
			min = 0;
		}
		gotoxy(60, 11);
		printf("\033[0;31mPress 'Esc' for exit \033[0;37m\n");
		displayTime(hour, min, sec);
		if (GetKeyState(VK_ESCAPE) < 0)
		{
			system("cls");
			check_start_start(); // (+)
		}
	}
}