#include <windows.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <boost/algorithm/string.hpp>
#include "all_diclarations.h"

#pragma warning(disable : 4996).

using namespace std;

int InjectDLL(DWORD, char*);
int getDLLpath(char*);
int getPID(int*);
int getProc(HANDLE*, DWORD);

int getDLLpath(char* dll)
{
	cout << "\n\033[0;31mEnter 'esc' (for exit)\033[0;37m";
	cout << "\n\033[0;33mEnter path to DLL file: \033[0;37m";
	cin >> dll;
	std::string str = dll;
	boost::to_lower(str);
	boost::trim(str);
	if (str == "esc")
	{
		check_start_start();
	}
	return 1;
}

int getPID(int* PID)
{
	cout << "\n\033[0;31mEnter 'esc' (for exit)\033[0;37m";
	cout << "\n\033[0;33mEnter PID to target process: \033[0;37m";
	cin >> *PID;
	std::string str = std::to_string(*PID);
	boost::to_lower(str);
	boost::trim(str);
	if (str == "esc")
	{
		check_start_start();
	}
	return 1;
}

int getProc(HANDLE* handleToProc, DWORD pid)
{
	*handleToProc = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
	DWORD dwLastError = GetLastError();

	if (*handleToProc == NULL)
	{
		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		printf("(!Unable to open process!)\n");
		printf("\033[0;37m");
		_getch();
		cin.clear();
		check_start_start();

		return -1;
	}
	else
	{
		//cout << "Process opened \033[0;32msuccessfully!\033[0;37m\n";
		printf("\033[0;32m");
		printf("\n");
		printf("(!SUCCESS!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;33m");
		printf("(!Process opened successfully!)\n");
		printf("\033[0;37m");
		//getch();
		check_start_start();
		return 1;
	}
}

int InjectDLL(DWORD PID, char* dll)
{
	HANDLE handleToProc;
	LPVOID LoadLibAddr;
	LPVOID baseAddr;
	HANDLE remThread;

	int dllLength = strlen(dll) + 1;

	if (getProc(&handleToProc, PID) < 0)
		return -1;

	LoadLibAddr = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");

	if (!LoadLibAddr)
		return -1;

	baseAddr = VirtualAllocEx(handleToProc, NULL, dllLength, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	if (!baseAddr)
		return -1;

	if (!WriteProcessMemory(handleToProc, baseAddr, dll, dllLength, NULL))
		return -1;

	remThread = CreateRemoteThread(handleToProc, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibAddr, baseAddr, 0, NULL);

	if (!remThread)
		return -1;

	WaitForSingleObject(remThread, INFINITE);

	VirtualFreeEx(handleToProc, baseAddr, dllLength, MEM_RELEASE);

	if (CloseHandle(remThread) == 0)
	{
		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		printf("(!Failed to close handle to remote thread!)\n");
		printf("\033[0;37m");
		cin.clear();
		getch();
		check_start_start();

		return -1;
	}

	if (CloseHandle(handleToProc) == 0)
	{
		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		printf("(!Falied to close handle to target process!)\n");
		printf("\033[0;37m");
		cin.clear();
		getch();
		check_start_start();

		return -1;
	}

}

void inject_prog_start()
{
	int PID = -1;
	char* dll = new char[255];

	getDLLpath(dll);
	getPID(&PID);

	InjectDLL(PID, dll);

	check_start_start(); 
}