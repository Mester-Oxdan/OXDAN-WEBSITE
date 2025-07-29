#include <windows.h>
#include <conio.h>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include "all_diclarations.h"

#pragma warning(disable : 4996).

using namespace std;

bool isNumber22(string s)
{
	for (int i = 0; i < s.length(); i++)
		if (isdigit(s[i]) == false)
			return false;

	return true;
}

void guess_number_start()
{
	system("cls");
	srand(time(0));
	int x = rand() % 101;
	int attempt = 0;
	string answer;

	int left, right;
	left = 1;
	right = 100;

	while (true)
	{
		try
		{
			printf("\n\033[0;31mEnter 'esc' (for exit) \033[0;37m");
			cout << "\n\033[0;33mGuess number (\033[0;31m" << to_string(left) << "\033[0;37m - \033[0;32m" << to_string(right) << "\033[0;33m): \033[0;37m";
			cin >> answer;
			boost::to_lower(answer);
			boost::trim(answer);
			if (answer == "esc")
			{
				check_start_start();
			}

			else if (!(isNumber22(answer)))
			{
				printf("\033[0;31m");
				printf("\n");
				printf("(!ERROR!)");
				printf("\033[0;37m");
				printf(" = ");
				printf("\033[0;32m");
				printf("(!Only integers!)\n");
				printf("\033[0;37m");
				getch();

				guess_number_start();
			}

			attempt++;

			if (atoi(answer.c_str()) > x)
			{
				cout << "\nMy number: (\033[0;31m!Lower!\033[0;37m)\n" << endl;
				right = atoi(answer.c_str()) - 1;
			}

			if (atoi(answer.c_str()) < x)
			{
				cout << "\nMy number: (\033[0;32m!Bigger!\033[0;37m)\n" << endl;
				left = atoi(answer.c_str()) + 1;
			}

			if (atoi(answer.c_str()) == x)
			{
				cout << "\nWell you guess my number (it is: \033[0;33m" << x << "\033[0;37m)" << endl;
				cout << "You needed: \033[0;33m" << attempt << "\033[0;37m attempts for this" << endl;

				check_start_start(); // (+)
			}
		}

		catch (...)
		{
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Only integers!)\n");
			printf("\033[0;37m");

			guess_number_start();
		}
	}
}