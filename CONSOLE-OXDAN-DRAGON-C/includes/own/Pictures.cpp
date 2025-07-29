#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "all_diclarations.h"

#pragma warning(disable : 4996).

using namespace std;

void Pictures()
{

	if (x == "author") // author (+)
	{
		try
		{
			author_start();
		}
		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "ukraine") // ukraine (+)
	{
		try
		{
			ukraine_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "matrix") // matrix (+)
	{
		try 
		{
			matrix_start();
		}
		
		catch (...)
		{
			check_start_start();
		}
	}
}