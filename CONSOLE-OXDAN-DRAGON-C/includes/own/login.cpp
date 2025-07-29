#include <windows.h>
#include <iostream>
#include <conio.h>
#include <string.h>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include "all_diclarations.h"

#pragma warning(disable : 4996).

using namespace std;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

bool isNumber(string s)
{
	for (int i = 0; i < s.length(); i++)
		if (isdigit(s[i]) == false)
			return false;

	return true;
}

bool found_password = false;

void login()
{
	int count = 0;
	string user, pass, u, p;
	system("cls");
	gotoxy(46, 8);
	cout << "\033[0;31mEnter 'esc' (for exit) \033[0;37m";
	gotoxy(51, 9);
	cout << "\033[0;31mLOGIN: \033[0;37m";
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN);
	gotoxy(50, 11);
	cout << "USERNAME: ";
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
	cin >> user;
	boost::to_lower(user);
	boost::trim(user);
	if (user == "esc")
	{
		first_start();
	}

	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN);
	gotoxy(50, 12);
	cout << "PASSWORD: ";
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
	cin >> pass;
	boost::to_lower(pass);
	boost::trim(pass);
	if (pass == "esc")
	{
		first_start();
	}

	ifstream input(oxdan_dragon_c + "\\includes\\own\\resuorces\\all_txt\\login_data_base.txt");
	while (input >> u >> p)
	{

		for (int i = 0; i < p.length(); i++)
		{
			p[i] -= 87;
		}

		if (u == user && p == pass)
		{
			found_password = true;
			system("cls");
			printf("\033[0;33mOxdan"); // intro cmd (+)
			printf("\033[0;31m Dragon");
			printf("\033[0;37m [ Version: 1.2025 [ENGLISH] (C/C++) [WINDOWS] ] \n");
			printf("(p) Oxdan Praduction. \n");
			start_start(true);
		}

		if (p == pass && u != user)
		{
			found_password = true;
			gotoxy(50, 14);
			printf("\033[0;31m");
			printf("\n");
			printf("                                         (!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Wrong username!)\n");
			printf("\033[0;37m");
			getch();
			first_start();
			//system("cls");
		}

		if (u == user && p != pass)
		{
			found_password = true;
			gotoxy(50, 14);
			printf("\033[0;31m");
			printf("\n");
			printf("                                         (!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Wrong password!)\n");
			printf("\033[0;37m");
			getch();
			first_start();
			//system("cls");
		}

		else
		{
			continue;
		}

	}
	input.close();

	if (found_password == false)
	{
		gotoxy(50, 14);
		printf("\033[0;31m");
		printf("\n");
		printf("                                         (!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		printf("(!Account did not found!)\n");
		printf("\033[0;37m");
		getch();
		first_start();
	}
}