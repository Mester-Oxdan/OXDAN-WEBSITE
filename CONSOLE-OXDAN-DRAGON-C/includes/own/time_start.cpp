#include <windows.h>
#include <iostream>
#include "all_diclarations.h"

using namespace std;

void time_start()
{
	system("cls");
	SYSTEMTIME st;
	while (true)
	{
		GetLocalTime(&st);
		gotoxy(60, 11);
		printf("\033[0;31mPress 'Esc' for exit \033[0;37m\n");
		gotoxy(60, 12);
		cout << "     " << st.wHour << " " << st.wMinute << " " << st.wSecond << endl;
		Sleep(1000);
		system("cls");
		if (GetKeyState(VK_ESCAPE) < 0)
		{
			//system("cls");
			check_start_start(); // (+)
		}
	}
}