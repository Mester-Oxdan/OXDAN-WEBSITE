#include <windows.h>
#include <iostream>
#include <shlobj_core.h>
#include <time.h>
#include "all_diclarations.h"

using namespace std;

void con_wifi_start()
{

	string filePath = oxdan_dragon_c + "/includes/own/test_python_py_con_wifi.py";
	vector<string> directories;

	// Split the path into directories and add them to the list
	size_t start = 0, end;
	while ((end = filePath.find("\\", start)) != string::npos) {
		string dir = filePath.substr(start, end - start);
		directories.push_back(dir);
		start = end + 1;
	}
	string lastComponent = filePath.substr(start);
	directories.push_back(lastComponent);

	// Keep track of the first and last words with spaces
	string firstSpaceWord;
	string lastSpaceWord;

	// Print the list of directories and detect first/last words with spaces
	//cout << "Original Path: " << filePath << endl;
	//cout << "List: ";
	for (const string& dir : directories) {
		//cout << "\"" << dir << "\" ";

		if (containsSpaces_2(dir)) {
			if (firstSpaceWord.empty()) {
				firstSpaceWord = dir;
			}
			lastSpaceWord = dir;
		}
	}
	//cout << endl;

	// Print the first and last words with spaces
	if (!firstSpaceWord.empty()) {
		//cout << "First word with spaces: " << firstSpaceWord << endl;
		//cout << "Last word with spaces: " << lastSpaceWord << endl;

		if (firstSpaceWord == lastSpaceWord)
		{

			// Replace spaces within the first and last words with double quotes
			size_t startPos = filePath.find(firstSpaceWord);
			size_t endPos = startPos + firstSpaceWord.length();
			string modifiedPath = filePath.substr(0, startPos) + "\"" + firstSpaceWord + filePath.substr(endPos);

			startPos = modifiedPath.find(lastSpaceWord);
			endPos = startPos + lastSpaceWord.length();
			modifiedPath = modifiedPath.substr(0, startPos) + lastSpaceWord + "\"" + modifiedPath.substr(endPos);


			// Print the modified path
			//cout << "Modified Path: " << modifiedPath << endl;
			string cmd_cmd = "start ";
			cmd_cmd += modifiedPath;
			system(cmd_cmd.c_str());
		}
		else
		{
			// Replace spaces within the first and last words with double quotes
			size_t startPos = filePath.find(firstSpaceWord);
			size_t endPos = startPos + firstSpaceWord.length();
			string modifiedPath = filePath.substr(0, startPos) + "\"" + firstSpaceWord + "\"" + filePath.substr(endPos);

			startPos = modifiedPath.find(lastSpaceWord);
			endPos = startPos + lastSpaceWord.length();
			modifiedPath = modifiedPath.substr(0, startPos) + "\"" + lastSpaceWord + "\"" + modifiedPath.substr(endPos);


			// Print the modified path
			//cout << "Modified Path: " << modifiedPath << endl;
			string cmd_cmd = "start ";
			cmd_cmd += modifiedPath;
			system(cmd_cmd.c_str());
		}
	}
	else {
		//cout << "No words with spaces found." << endl;
	}
	//cout << "pt 2: oxidan_dragpn_c =" << oxdan_dragon_c << endl;
	//_getch();
	//string cmd_3 = "/includes/own/test_python_py_doom.py";
	//string cmd_33 = "start " + oxdan_dragon_c + cmd_3;
	//string cmd_33 = "C:\\Users\\bogda\\Downloads\\"Oxdan-Dragon-C - Copy\\test jy"\\CONSOLE - OXDAN - DRAGON - C\\CONSOLE - OXDAN - DRAGON - C++.exe";
	//cout << "pt 3: cmd_33= " << cmd_33 << endl;
	//_getch();
	system(filePath.c_str());
	check_start_start();
}