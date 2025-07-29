#include <windows.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include "all_diclarations.h"

#pragma warning(disable : 4996).

using namespace std;

void inject_prog_2_start()
{
    string cmd_1 = "/includes/own/test_python_py_file_injector.py";
    string cmd_11 = "start " + oxdan_dragon_c + cmd_1;
    system(cmd_11.c_str());
    check_start_start();
 
}
