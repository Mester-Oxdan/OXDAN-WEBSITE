#include <windows.h>

void hideCursor() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cInfo;

	GetConsoleCursorInfo(hOut, &cInfo); //get cursor info for current output handle
	cInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(hOut, &cInfo); //set cursor info
}