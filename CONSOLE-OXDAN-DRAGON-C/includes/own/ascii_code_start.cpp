#include <windows.h>
#include <conio.h>
#include <iostream>
#include "all_diclarations.h"

using namespace std;

void ascii_code_start()
{
	system("cls");
	char ch;
	gotoxy(53, 11);
	printf("\033[0;31mPress 'Esc' for exit\033[0;37m\n");

	gotoxy(50, 12);
	printf("\033[0;33mPress any key (ESC == 27)\033[0;37m\n");

	while (true)
	{
		if (GetKeyState(VK_ESCAPE) < 0) check_start_start(); // (+)
		//gotoxy(60, 8);

		ch = _getch();
		if (ch == -32) ch = _getch();
		gotoxy(58, 13);
		cout << "code " << (int)ch << " " << endl;
	}
}