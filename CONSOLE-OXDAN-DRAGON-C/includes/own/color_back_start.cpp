#include <windows.h>
#include <string>
#include <fstream>
#include "all_diclarations.h"

void color_back_start(string name)
{
	if (name == "bl" || name == "BL") // Black (+)
	{
		system("color 07");

		check_start_start();
	}
	else if (name == "r" || name == "R") // Red (+)
	{
		system("color 47");
		
		check_start_start();
	}
	else if (name == "g" || name == "G") // Green (+)
	{
		system("color 27");

		check_start_start();
		
	}
	else if (name == "y" || name == "Y") // Yellow (+)
	{
		system("color 67");
		
		check_start_start();
	}
	else if (name == "b" || name == "B") // Blue (+)
	{
		system("color 17");

		check_start_start();
	}
	else if (name == "p" || name == "P") // Purple (+)
	{
		system("color 57");
		
		check_start_start();
	}
	else if (name == "wb" || name == "WB") // White/Blue (+)
	{
		system("color 37");
		
		check_start_start();
	}
	else if (name == "w" || name == "W") // White (+)
	{
		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		printf("(!Enter color_back option!)\n");
		printf("\033[0;37m");
	}
	else // White (+)
	{
		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		printf("(!Enter color_back option!)\n");
		printf("\033[0;37m");
	}
}