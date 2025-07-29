#include <windows.h>
#include <iostream>
#include <conio.h>
#include "all_diclarations.h"

using namespace std;

void instructions_rules()
{
    system("cls");
    std::cout << std::endl;
    Sleep(1);
    std::cout << std::endl;
    Sleep(1);
    std::cout << "\033[0;31m                                                           !RULES!\033[0;37m" << std::endl;
    Sleep(1);
    std::cout << std::endl;
    Sleep(1);
    std::cout << "   First command which you need to know is \033[0;33m-h\033[0;37m, this command will show all commands which this console have." << std::endl;
    Sleep(1);
    std::cout << std::endl;
    Sleep(1);
    std::cout << "\033[0;31m   !\033[0;33mRemember\033[0;37m, Author don't care and he is not responsible for what you doing." << std::endl;
    Sleep(1);
    std::cout << std::endl;
    Sleep(1);
    std::cout << "   This console was created in purposes of learning coding." << std::endl;
    Sleep(1);
    std::cout << std::endl;
    Sleep(1);
    std::cout << "   You always can find code of this console on (https://github.com/Mester-Oxdan) Author github." << std::endl;
    Sleep(1);
    std::cout << std::endl;
    Sleep(1);
    std::cout << "\033[0;31m                                                   Press any key to go back.\033[0;37m" << std::endl;
    Sleep(1);
    _getch();
    check_start_start();
}