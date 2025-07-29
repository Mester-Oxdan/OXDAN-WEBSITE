#include <windows.h>
#include "all_diclarations.h"

#pragma warning(disable : 4996).

void SetWindow(int xc, int yc)
{
	_COORD coord;
	coord.X = 152;
	coord.Y = 600;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = xc; //set size of console 1 (+) 33
	Rect.Right = yc; //set size of console 1 (+) 142

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle 
	SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size 
	SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size 
}