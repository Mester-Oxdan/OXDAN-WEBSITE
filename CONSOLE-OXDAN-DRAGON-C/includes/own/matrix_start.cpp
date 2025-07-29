#include <windows.h>
#include <iostream>
#include "all_diclarations.h"

using namespace std;

int Modulus(int iN, int iMod) 
{
	int iQ = (iN / iMod);
	return iN - (iQ * iMod);
}

char GetChar(int iGenerator, char cBase, int iRange) 
{
	return (cBase + Modulus(iGenerator, iRange));
}

void matrix_start()
{
	system("mode 141, 29"); // set size of console (+)
	SetWindow(141, 29); // set buffer size of console (+)
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 2);

	char caRow[80];
	int j = 7;
	int k = 2;
	int l = 5;
	int m = 1;
	while (true) {
		// Output a random row of characters
		for (int i = 0; i < 80; ++i)
		{
			if (caRow[i] != ' ') {
				caRow[i] = GetChar(j + i * i, 33, 30);
				if (((i * i + k) % 71) == 0) {
					SetConsoleTextAttribute(hConsole, 7);
				}
				else {
					SetConsoleTextAttribute(hConsole, 2);
				}
			}
			std::cout << caRow[i];
			SetConsoleTextAttribute(hConsole, 2);
		}
		j = (j + 31);
		k = (k + 17);
		l = (l + 47);
		m = (m + 67);
		caRow[Modulus(j, 80)] = '-';
		caRow[Modulus(k, 80)] = ' ';
		caRow[Modulus(l, 80)] = '-';
		caRow[Modulus(m, 80)] = ' ';
		// Delay
		Sleep(1);
		if (GetKeyState(VK_ESCAPE) < 0)
		{
			printf("\n\033[0;37m");
			check_start_start(); // (+)
		}
	}
}