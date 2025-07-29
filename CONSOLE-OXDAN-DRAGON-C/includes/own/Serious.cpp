#include <iostream>
#include <windows.h>
#include <conio.h>
#include <math.h>
#include <stack>
#include <iomanip>
#include <sstream>
#include "all_diclarations.h"

#pragma warning(disable : 4996).

using namespace std;

void Serious()
{
	if (x == "tim" || x == "time") // tim (+)
	{
		try
		{
			time_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}
	if (x == "chat") // chat (+)
	{
		try
		{
			chat_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	if (x == "screen_recorder") // screen_recorder (+)
	{
		try
		{
			screen_recorder_start();
			check_start_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	if (x == "notepad") // notepad (+)
	{
		try
		{
			notepad_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}
	if (x == "3d_price_calc") // 3d_price_calc (+)
	{
		try
		{
			d_price_calc_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}
	
	if (x == "translator") // translator (+)
	{
		try
		{
			string cmd_1 = "/includes/own/test_python_py_translator.py";
			string cmd_11 = "start " + oxdan_dragon_c + cmd_1;
			system(cmd_11.c_str());
			check_start_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "stopwatch") // stopwatch (+)
	{

		try
		{
			stopwatch_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "webcam_recorder") // webcam_recorder (+)
	{

		try
		{
			webcam_recorder_start();
		}

		catch (...)
		{
			check_start_start();
		}

	}

	else if (x == "dictaphone") // dictaphone (+)
	{

		try
		{
			dictaphone_start();
		}

		catch (...)
		{
			check_start_start();
		}

	}

	else if (x == "timer") // timer (+)
	{

		try
		{
			timer_start();
		}

		catch (...)
		{
			check_start_start();
		}

	}

	else if (x == "cur_conv") // cur_conv (+)
	{

		try
		{
			cur_conv_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "calendar") // calendar (+)
	{

		try
		{
			calendar_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "calculator") // calculator (+)
	{

		try
		{
			calculator_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}
}