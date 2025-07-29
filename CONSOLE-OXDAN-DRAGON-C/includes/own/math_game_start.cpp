#include <iostream>
#include <conio.h> 
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include "all_diclarations.h"

#pragma warning(disable : 4996).

using namespace std;

void math_game_start() 
{
	try
	{
		int level, limit, totalNo;
		limit = 100;
		string option;

		system("cls");
		printf("\n\033[0;31mWrite 'esc' (for exit) \033[0;37m\n");
		cout << "\033[0;33mEnter total questions: \033[0;37m";
		cin >> totalNo;
		cout << "\n\033[0;33mChoose Level: \033[0;37m";
		Sleep(170);
		cin >> option;
		cout << endl;

		if (option == "esc" || to_string(totalNo) == "esc")
		{
			cin.clear();
			cin.ignore();
			check_start_start();
		}

		float q1, q2, correctAns;
		int ans;
		int correctNo = 0;
		char operation;

		while (option != "esc")
		{
			if (stoi(option))
			{
				srand(time(0));

				for (int i = 0; i < totalNo; i++) {
					q1 = rand() % limit;
					q2 = rand() % limit;

					int tmpOp = rand() % 4;
					switch (tmpOp) {
					case 0: operation = '+'; break;
					case 1: operation = '-'; break;
					case 2: operation = '*'; break;
					case 3: operation = '/'; break;
					}

					cout << "(" << (i + 1) << ") ";
					cout << q1 << " " << operation << " " << q2 << " = ";
					cin >> ans;

						switch (operation) {
						case '+': correctAns = q1 + q2; break;
						case '-': correctAns = q1 - q2; break;
						case '*': correctAns = q1 * q2; break;
						case '/': correctAns = q1 / q2; break;
						}

						if (round(correctAns) == ans) {
							correctNo++;
							cout << "\n\033[0;32mCorrect\033[0;37m" << endl << endl;
						}
						else {
							cout << "\n\033[0;31mWrong\033[0;37m" << endl;
							cout << "\n\033[0;33mAnswer: \033[0;37m" << round(correctAns) << endl << endl;
						}
				}

				cout << "\033[0;33mTotal: \033[0;37m" << totalNo << endl;
				cout << "\033[0;32mCorrect: \033[0;37m" << correctNo << endl << endl;

				getch();
				cin.clear();
				cin.ignore();
				check_start_start();
			}
			else
			{
				cin.clear();
				cin.ignore();
				check_start_start();
			}
		}
	}

	catch (...)
	{
		cin.clear();
		cin.ignore();
		check_start_start();
    }
}
