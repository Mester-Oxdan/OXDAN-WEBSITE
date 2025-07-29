#include <windows.h>
#include <iostream>
#include <conio.h>
#include <string.h>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include "all_diclarations.h"

#pragma warning(disable : 4996).

using namespace std;

bool found_password_9 = false;

void my_accounts_start()
{
	int count_9 = 0;
	string u_9, p_9;

	ifstream input_9(oxdan_dragon_c + "\\includes\\own\\resuorces\\all_txt\\login_data_base.txt");
	printf("\n");
	cout << "\033[0;31m     YOUR ACCOUNTS: \033[0;37m\n";
	cout << "\033[0;33mUSERNAME:      PASSWORD:\033[0;37m\n";
	while (input_9 >> u_9 >> p_9)
	{

		for (int i = 0; i < p_9.length(); i++)
		{
			p_9[i] -= 87;
		}

		cout << "    " << u_9 << "          " << "    " << p_9 << endl;
		Sleep(1);
		continue;

	}
	input_9.close();

	check_start_start();
}