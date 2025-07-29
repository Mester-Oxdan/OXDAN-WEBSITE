#include <windows.h>
#include <iostream>
#include <string>
//#include <raylib.h>
#include "all_diclarations.h"

using namespace std;

void show_messagebox(string enter_response_yes)
{

	int messageboxid = MessageBoxA(NULL, (LPCSTR)enter_response_yes.c_str(), "Response: ", MB_ICONASTERISK);

	switch (messageboxid)
	{
	case IDOK:

		check_start_start();
		//WindowShouldClose();

	default:

		check_start_start();
		//WindowShouldClose();
	}
}