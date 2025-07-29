#include <windows.h>
#include <iostream>
#include "all_diclarations.h"

using namespace std;

void Pranks()
{
	if (x == "prank_button") // prank_button (+)
	{

		if (tokens.size() < 2)
		{
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Enter prank_button option!)\n");
			printf("\033[0;37m");
		}

		else
		{
			try
			{
				string atr = tokens[1];

				if (atr == "no")
				{
					prank_button_no();
				}

				if (atr == "yes")
				{
					prank_button_yes();
				}
				else {
					printf("\033[0;31m");
					printf("\n");
					printf("(!ERROR!)");
					printf("\033[0;37m");
					printf(" = ");
					printf("\033[0;32m");
					printf("(!Enter prank_button option!)\n");
					printf("\033[0;37m");
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
				printf("(!Enter prank_button option!)\n");
				printf("\033[0;37m");
			}
		}

		check_start_start();
	}

	if (x == "melt_screen") // melt_screen (+)
	{
		prank_melt_screen_start();
	}

	if (x == "gdi_virus") // gdi_virus (+)
	{
		gdi_virus_start();
	}

}