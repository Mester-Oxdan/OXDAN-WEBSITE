#include <string>
#include <windows.h>
#include "all_diclarations.h"

void color_start(string name)
{

	if (name == "bl" || name == "BL") // Black (+)
	{
		printf(" \033[0;30m");
		check_start_start();
	}
	else if (name == "r" || name == "R") // Red (+)
	{
		printf(" \033[0;31m");
		check_start_start();
	}
	else if (name == "g" || name == "G") // Green (+)
	{
		printf(" \033[0;32m");
		//system("color a");
		check_start_start();
	}
	else if (name == "y" || name == "Y") // Yellow (+)
	{
		printf(" \033[0;33m");
		check_start_start();
	}
	else if (name == "b" || name == "B") // Blue (+)
	{
		printf(" \033[0;34m");
		check_start_start();
	}
	else if (name == "p" || name == "P") // Purple (+)
	{
		printf(" \033[0;35m");
		check_start_start();
	}
	else if (name == "wb" || name == "WB") // White/Blue (+)
	{
		printf(" \033[0;36m");
		check_start_start();
	}
	else if (name == "w" || name == "W") // White (+)
	{
		printf(" \033[0;37m");
		check_start_start();
	}
	else // White (+)
	{
		printf(" \033[0;37m");
		check_start_start();
	}
}