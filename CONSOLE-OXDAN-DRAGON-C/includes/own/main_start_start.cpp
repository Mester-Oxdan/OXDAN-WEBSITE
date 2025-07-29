#include <windows.h>
#include <string>
#include <fstream>
#include "all_diclarations.h"

void main_start_start(string man, bool willstart)
{
	if (man == "off")
	{
		//willstart = false;
		//check_start_start();

		std::fstream txt_yes_no(oxdan_dragon_c + "\\includes\\own\\resuorces\\all_txt\\txt_yes_no.txt", ios::out | ios::trunc); //open in constructor
		std::string data("false");
		txt_yes_no << data << endl;

		start_start(false);
	}

	else if (man == "on")
	{
		//willstart = true;
		//check_start_start();

		std::fstream txt_yes_no(oxdan_dragon_c + "\\includes\\own\\resuorces\\all_txt\\txt_yes_no.txt", ios::out | ios::trunc); //open in constructor
		std::string data("true");
		txt_yes_no << data << endl;

		start_start(true);
	}

	else
	{
		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		printf("(!Enter &main option!)\n");
		printf("\033[0;37m");
	}

	check_start_start();
}