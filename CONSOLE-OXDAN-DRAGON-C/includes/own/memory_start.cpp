#include <windows.h>
#include <atlstr.h>
#include <iostream>
#include "all_diclarations.h"
#include <conio.h>
#include <iomanip> // For std::setprecision

using namespace std;

bool dirExists(const std::string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!

	return false;    // this is not a directory!
}

void GetInfo()
{
	int n;
	bool Flag;
	DWORD dr = GetLogicalDrives(); // функция возвращает битовую маску
	for (int x = 0; x < 26; x++) // прогоняем по битам
	{
		n = ((dr >> x) & 1); // определяем значение текущего бита
		if (n) // если единица - диск с номером x есть
		{
			//переобразовуємо TCHAR to string
			std::string DiskName(CT2CA(CString(TCHAR(65 + x))));//отримуємо літеру диска
			string lPath = DiskName + ":\\";//отримуємо назву диска
			WORD OldErrorMode;
			OldErrorMode = SetErrorMode(SEM_FAILCRITICALERRORS); // убираем показ ошибок
			bool ready = dirExists(lPath); // пытаемcя открыть корневую директорию
			SetErrorMode(OldErrorMode); // восстанавливаем старый режим показа ошибок
			if (ready)
			{
				UINT drive_type = GetDriveTypeA(lPath.c_str()); // определяем тип диска
				
				unsigned __int64 FreeBytesAvailable;
				unsigned __int64 TotalNumberOfBytes;
				unsigned __int64 TotalNumberOfFreeBytes;

				//конвертуємо нашу строку в wstring а потім у LPCWSTR
				wstring temp = wstring(lPath.begin(), lPath.end());
				LPCWSTR lLPCWSTRPath = temp.c_str();

				Flag = ::GetDiskFreeSpaceEx(lLPCWSTRPath,
					(PULARGE_INTEGER)&FreeBytesAvailable,
					(PULARGE_INTEGER)&TotalNumberOfBytes,
					(PULARGE_INTEGER)&TotalNumberOfFreeBytes);

				if (Flag)
				{
					__int64 FreeGiga = TotalNumberOfFreeBytes / 1073741824;
					__int64 TotalGiga = TotalNumberOfBytes / 1073741824;
					cout << "\n\033[0;33mDisk Device: " + DiskName + ":/\n";
					Sleep(1);
					cout << "\033[0;33mTotal space: \033[0;37m" + to_string(TotalGiga) + " GB" + "\n";
					Sleep(1);
					cout << "\033[0;32mFree space: \033[0;37m" + to_string(FreeGiga) + " GB" + "\n";
					Sleep(1);
					cout << "\033[0;31mUsed space: \033[0;37m" + to_string(TotalGiga - FreeGiga) + " GB" + "\n";
					Sleep(1);
				}
				else
				{
					printf("\033[0;31m");
					printf("\n");
					printf("(!ERROR!)");
					printf("\033[0;37m");
					printf(" = ");
					printf("\033[0;32m");
					printf("(!Get Disk Free Space!)\n");
					printf("\033[0;37m");
					//_getch();
					check_start_start();
				}

				cout << "\033[0;35mDisk type: \033[0;37m";
				Sleep(1);
				if (drive_type == DRIVE_REMOVABLE) cout << "REMOVABLE";
				else if (drive_type == DRIVE_FIXED)     cout << "FIXED";
				else if (drive_type == DRIVE_REMOTE)    cout << "REMOTE";
				else if (drive_type == DRIVE_CDROM)     cout << "CD-ROM";
				else if (drive_type == DRIVE_RAMDISK)   cout << "RAMDISK";

				else 
				{ 
					printf("\033[0;31m");
					printf("\n");
					printf("(!ERROR!)");
					printf("\033[0;37m");
					printf(" = ");
					printf("\033[0;32m");
					printf("(!Unknown disk type!)\n");
					printf("\033[0;37m");
					check_start_start();
				}

				USES_CONVERSION_EX;
				LPWSTR afjha = A2W_EX(lPath.c_str(), lPath.length());
				_TCHAR FileSysteNameT[32] = _T("");
				Flag = GetVolumeInformation(afjha, NULL, NULL, NULL, NULL, NULL, FileSysteNameT, 32);

				wstring FileSysteNameW(&FileSysteNameT[0]); //convert to wstring
				string FileSysteNameS(FileSysteNameW.begin(), FileSysteNameW.end()); //and convert to string.

				if (Flag)
				{
					cout << "\n\033[0;36mFiles system: \033[0;37m" + FileSysteNameS + "\n";
					Sleep(1);
				}

				else
				{
					printf("\033[0;31m");
					printf("\n");
					printf("(!ERROR!)");
					printf("\033[0;37m");
					printf(" = ");
					printf("\033[0;32m");
					printf("(!Something went wrong with your files system!)\n");
					printf("\033[0;37m");
					check_start_start();
				}
			}
		}
	}
}

void memory_start()
{
	GetInfo();
	check_start_start();
}