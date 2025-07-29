#include <windows.h>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include "all_diclarations.h"

#pragma warning(disable : 4996).

using namespace std;

void registration()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	string reguser, regpass, ru, rp;
	system("cls");
	gotoxy(46, 8);
	cout << "\033[0;31mEnter 'esc' (for exit) \033[0;37m";
	gotoxy(49, 9);
	cout << "\033[0;31mREGISTRATION: \033[0;37m";
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN);
	gotoxy(50, 11);
	cout << "USERNAME: ";
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
	cin >> reguser;
	boost::to_lower(reguser);
	boost::trim(reguser);
	if (reguser == "esc")
	{
		first_start();
	}

	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN);
	gotoxy(50, 12);
	cout << "PASSWORD: ";
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
	cin >> regpass;
	boost::to_lower(regpass);
	boost::trim(regpass);
	if (regpass == "esc")
	{
		first_start();
	}

	string keyregpass = regpass;

	for (int i = 0; i < keyregpass.length(); i++)
	{
		keyregpass[i] += 87;
	}

	try
	{
		string u, p;
		ifstream input(oxdan_dragon_c + "\\includes\\own\\resuorces\\all_txt\\login_data_base.txt");
		while (input >> u >> p)
		{
			for (int i = 0; i < p.length(); i++)
			{
				p[i] -= 87;
			}

			if (p == regpass)
			{
				gotoxy(50, 14);
				printf("\033[0;31m");
				printf("\n");
				printf("                                         (!ERROR!)");
				printf("\033[0;37m");
				printf(" = ");
				printf("\033[0;32m");
				printf("(!Password already exist!)\n");
				printf("\033[0;37m");
				getch();
				first_start();
				system("cls");
			}

			if (u == reguser)
			{
				gotoxy(50, 14);
				printf("\033[0;31m");
				printf("\n");
				printf("                                         (!ERROR!)");
				printf("\033[0;37m");
				printf(" = ");
				printf("\033[0;32m");
				printf("(!Username already exist!)\n");
				printf("\033[0;37m");

				getch();
				first_start();
				system("cls");
			}

		}
		input.close();
	}
	catch (...)
	{
		ofstream reg(oxdan_dragon_c + "\\includes\\own\\resuorces\\all_txt\\login_data_base.txt", ios::app);
		reg << reguser << ' ' << keyregpass << endl;

		gotoxy(50, 14);
		cout << "\033[0;32m!REGISTRATION SUCCESSFUL!\033[0;37m";
		_getch();

		first_start();
	}

	ofstream reg(oxdan_dragon_c + "\\includes\\own\\resuorces\\all_txt\\login_data_base.txt", ios::app);
	reg << reguser << ' ' << keyregpass << endl;

	gotoxy(45, 14);
	cout << "\033[0;32m!REGISTRATION SUCCESSFUL!\033[0;37m";
	_getch();

	first_start();
}