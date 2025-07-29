#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

void show_messagebox_1(string enter_response_yes)
{

	int messageboxid = MessageBoxA(NULL, (LPCSTR)enter_response_yes.c_str(), "Response: ", MB_ICONASTERISK);

	switch (messageboxid)
	{
	case IDOK:

		exit(0);

	default:

		exit(0);
	}
}