#include <windows.h>
#include <fstream>
#include <string>
#include <iostream>
#include <regex>
#include <boost/algorithm/string.hpp>
#include "all_diclarations.h"

using namespace std;

void del_account_start()
{
	string user, pass, u, p;
	bool del_account_bool = true;

	cout << "\n\033[0;31mEnter 'esc' (for exit)\033[0;37m";
	cout << "\n\033[0;33mEnter account name: \033[0;37m";
	cin >> user;
	boost::to_lower(user);
	boost::trim(user);
	if (user == "esc")
	{
		check_start_start();
	}

	cout << "\n\033[0;33mEnter account password: \033[0;37m";
	cin >> pass;
	boost::to_lower(pass);
	boost::trim(pass);
	if (pass == "esc")
	{
		check_start_start();
	}

	ifstream input(oxdan_dragon_c + "\\includes\\own\\resuorces\\all_txt\\login_data_base.txt");
	while (input >> u >> p)
	{

		for (int i = 0; i < p.length(); i++)
		{
			p[i] -= 87;
		}

		if (p == pass && u == user)
		{
			del_account_bool = false;
		}

		if (p == pass && u != user)
		{
			del_account_bool = false;
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Wrong username!)\n");
			printf("\033[0;37m");
			check_start_start();
		}

		if (u == user && p != pass)
		{
			del_account_bool = false;
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Wrong password!)\n");
			printf("\033[0;37m");
			check_start_start();
		}
	}
	input.close();

	if (del_account_bool == true)
	{
		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		printf("(!Account did not found!)\n");
		printf("\033[0;37m");
		check_start_start();
	}


	u = user;
	p = pass;

	for (int i = 0; i < p.length(); i++)
	{
		p[i] += 87;
	}

	std::ifstream in(oxdan_dragon_c + "\\includes\\own\\resuorces\\all_txt\\login_data_base.txt");
	std::string content((std::istreambuf_iterator<char>(in)),
		std::istreambuf_iterator<char>());
	in.close();

	std::string replaced = std::regex_replace(content, std::regex(u + " " + p), "");

	std::ofstream out(oxdan_dragon_c + "\\includes\\own\\resuorces\\all_txt\\login_data_base.txt");
	out << replaced;
	out.close();
	printf("\033[0;32m");
	printf("\n");
	printf("(!SUCCESS!)");
	printf("\033[0;37m");
	printf(" = ");
	printf("\033[0;33m");
	printf("(!Account deleted successfully!)\n");
	printf("\033[0;37m");
	check_start_start();
}