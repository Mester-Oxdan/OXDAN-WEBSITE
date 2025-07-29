#include <windows.h>
#include <string>
#include <iostream>
#include <conio.h>
#include <boost/algorithm/string.hpp>
#include "all_diclarations.h"

#pragma warning(disable : 4996).

using namespace std;

void changeVolume()
{
	INPUT ip = { 0 };
	ip.type = INPUT_KEYBOARD;
	ip.ki.wVk = VK_VOLUME_UP;   //or VOLUME_DOWN or MUTE
	SendInput(1, &ip, sizeof(INPUT));
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

bool isNumber2(string s)
{
	for (int i = 0; i < s.length(); i++)
		if (isdigit(s[i]) == false)
			return false;

	return true;
}

void timer_start()
{
	//system("cls");
	string h1, m1, s1;
	int number;
	printf("\n");

	cout << "\033[0;31mEnter 'esc' (for exit) \033[0;37m\n";
	cout << "\033[0;33mEnter number of Hours: \033[0;37m"; cin >> h1;

	boost::to_lower(h1);
	boost::trim(h1);

	if (h1 == "esc")
	{
		check_start_start();
	}

	else if (!(isNumber2(h1)))
	{
		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		printf("(!Only integers!)\n");
		printf("\033[0;37m");
		cin.clear();
		getch();

		check_start_start();
	}

	cout << "\n\033[0;31mEnter 'esc' (for exit) \033[0;37m";
	cout << "\n\033[0;33mEnter number of Minutes: \033[0;37m"; cin >> m1;

	boost::to_lower(m1);
	boost::trim(m1);

	if (m1 == "esc")
	{
		check_start_start();
	}

	else if (!(isNumber2(m1)))
	{
		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		printf("(!Only integers!)\n");
		printf("\033[0;37m");
		cin.clear();
		getch();

		check_start_start();
	}

	cout << "\n\033[0;31mEnter 'esc' (for exit) \033[0;37m";
	cout << "\n\033[0;33mEnter number of Seconds: \033[0;37m "; cin >> s1;

	boost::to_lower(s1);
	boost::trim(s1);

	if (s1 == "esc")
	{
		check_start_start();
	}

	else if (!(isNumber2(s1)))
	{
		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		printf("(!Only integers!)\n");
		printf("\033[0;37m");
		cin.clear();
		getch();

		check_start_start();
	}

	//timer(h, m, s);
	int h = atoi(h1.c_str());
	int m = atoi(m1.c_str());
	int s = atoi(s1.c_str());

	for (;;)
	{
		if (h == 0 && m == 0 && s == 0)
		{
			break;
		}
		if (s == 0 && m == 0)
		{
			m = 60;
			h--;
		}
		if (s == 0)
		{
			s = 60;
			m--;
		}

		system("cls");
		gotoxy(60, 9);
		printf("\033[0;31mPress 'Esc' for exit \033[0;37m\n");
		gotoxy(65, 11);
		cout << h << ":" << m << ":" << s--;
		Sleep(1000);

		if (GetKeyState(VK_ESCAPE) < 0)
		{
			//system("cls");
			printf("\n");
			check_start_start();
		}
	}

	for (int i = 0; i < 25; i++)
	{
		changeVolume();
	}

	if (GetKeyState(VK_ESCAPE) < 0)
	{
		//system("cls");
		printf("\n");
		check_start_start();
	}

	Beep(2500, 1000);

	if (GetKeyState(VK_ESCAPE) < 0)
	{
			//system("cls");
			printf("\n");
			check_start_start();
	}

	if (GetKeyState(VK_ESCAPE) < 0)
	{
		//system("cls");
		printf("\n");
		check_start_start();
	}

	printf("\n");
	check_start_start();
}