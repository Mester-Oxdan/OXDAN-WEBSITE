#include <windows.h>
#include "all_diclarations.h"

#pragma warning(disable : 4996).

void gotoxy(int x, int y) {

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD CursorPosition;

	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}