#include <Windows.h>
#include <iostream>
#include <vector>
#include <windows.h>
#include <string>
#include <conio.h>
#include "all_diclarations.h"

#pragma warning(disable : 4996).

using namespace std;

void menu()
{
	cout << "\n\033[0;31mPress 'Esc' (for exit) \033[0;37m\n";
}

void clicker()
{
	bool click = false; //sets click to false

	while (true)
	{

		click = true;

		if (GetAsyncKeyState(VK_ESCAPE)) //if 'Z' is pressed click = false
		{
			click = false;
			check_start_start();
		}
		if (click == true) // if click = true it will press the mouse button down and up really fast
		{
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(1); //you can adjust the speed of the click here
		}
	}
}

void auto_clicker_start()
{

	if (GetKeyState(VK_ESCAPE) < 0) check_start_start();

	menu();
	clicker();
}
