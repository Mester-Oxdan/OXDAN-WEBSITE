#include <windows.h>
#include <string>
#include "all_diclarations.h"

void open_start(string path45)
{
	string cmd;

	cmd = "start ";
	cmd += path45;
	system(cmd.c_str());

}