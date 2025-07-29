#include <windows.h>
#include "all_diclarations.h"

void cor_desk_start()
{
	HWND hwnd = GetConsoleWindow();

	LPPOINT pPnt;
	pPnt = (LPPOINT)malloc(sizeof(*pPnt));

	LPRECT rct;
	rct = (LPRECT)malloc(sizeof(*rct));
	GetClientRect(hwnd, rct);

	LPRECT rctScr;
	rctScr = (LPRECT)malloc(sizeof(*rctScr));
	GetClientRect(GetDesktopWindow(), rctScr);

	do
	{
		system("cls");
		gotoxy(53, 11);
		printf("\033[0;31mPress 'esc' (for exit) \033[0;37m\n");
		GetCursorPos(pPnt);
		gotoxy(50, 12);
		printf("\033[0;33mGlobal cursor pos: \033[0;37m%d, %d \n", pPnt[0].x, pPnt[0].y);

		gotoxy(50, 14);
		ScreenToClient(hwnd, pPnt);
		printf("\033[0;33mLocal cursor pos: \033[0;37m%d, %d \n", pPnt[0].x, pPnt[0].y);

		gotoxy(50, 16);
		printf("\033[0;33mClient size: \033[0;37m%d x %d \n", rct[0].right, rct[0].bottom);

		gotoxy(50, 18);
		printf("\033[0;33mScreen size: \033[0;37m%d x %d \n", rctScr[0].right, rctScr[0].bottom);

		Sleep(100);

	} while (GetKeyState(VK_ESCAPE) >= 0);
	check_start_start(); // (+)
}